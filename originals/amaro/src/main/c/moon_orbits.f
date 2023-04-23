      program moon_orbits
c     Ramdom moons and orbits 

      implicit double precision (a-z)
c================================================
c     copyright (c) Selden Ball 2012
      character*5 version/'v1.19'/
c     ALL RIGHTS RESERVED
c     license:
c     this program may be freely distributed for educational purposes
c     but any commercial use requires written permission from the author

c     changes:
c     1.01 cleaned up code so ftnchek doesn't complain so much
c     1.02 replaced calls to ran(dmy) by calls to randf()
c     1.03 explicit output formatting instead of just *
c     1.04 place orbits between existing orbits
c          instead of randomly within max radius
c     1.05 prefix moon by name of planet so it'll be unique in this star system
c     1.06 include option name when complaining about it being missing
c     1.07 include TestPlanet specs if appropriate
c     1.08 include program name in catalog file
c     1.09 randomize sma of moon "better"
c     1.10 randomize initial mass available 
c     1.11 add atmosphere for large moons
c     1.12 note "Earthlike?" for moons >0.75 Earth masses
c     1.13 more code cleanup
c     1.14 use color
c     1.15 make version variable
c     1.16 limit max planet radius: hill radius calcs fail
c     1.17 display planetary type
c     1.18 add rocky planet radius guesstimate
c     1.19 specify appropriate texture for test planet
c================================================
C     this program was developed using g77 v3.4.4 
c     it seems to work correctly with gfortran v4.5.3 after cleanup

c     compilation instructions:

c     g77 moon_orbits.f -o moon_orbits

c     usage
c     ./moon_orbits -?

c Note: all options require a space between the option and its value
c================================================

c     someday need to check for 
c     positive resonances:
c     1:2:4 in orbital periods
c     3:2, 4:3, 3:4, 3:5, 4:7, 1:2, 2:3, 2:4, 2:5
c     BUT need adequate separation in orbital phase
c     negative resonances:
c     1:1, (except for trojans? -- not likely with many perturbators)
c     3:1, 5:2, 7:3, 2:1, 7:6

      integer Nmoons,Nmoon,i,max_moons,Ntest
      integer masses(0:11),npc,mmp1,mmp2

      DATA MASSES/12*0/
c     hill radius = a(1-e)* (m/3M)^(1/3)

c     planet & star parameters

      parameter (max_moons = 200 )
      parameter (mmp1=max_moons+1)
      parameter (mmp2=max_moons+2) ! includes minimum and maximum radii

c     sma and hill radii of moons
      dimension Am (0:mmp1),Hm (0:mmp1)
      data Am/mmp2*0.0/,Hm/mmp2*0.0/

      character*20 Nameplanet,Namestar,FileName
c---------------------
      call get_args
     * (FileName,Nameplanet,Mplanet,Rplanet,Aplanet, NameStar,Mstar,
     *  Nmoons,version)
      print *, Nmoons
      call str_len(FileName,npc)


      if (Nmoons.gt.200) then
         print *, 'Nmoons (',Nmoons,') is more than 200. Set to 200.'
         Nmoons=200
      endif

      open(1,file='Moons_'//FileName(:npc)//'.ssc',status='replace')

      write (1,*) '# moon catalog for Celestia generated by'
      write (1,*) '# moon_orbits '//version

c     Scaling parameters
      Mjup = 317.82 d0       ! mass of Jupiter in earth masses
      Rjup = 71 492.0 d0     ! radius of Jupiter in km (equatorial)
      Msol = 332 918.215 d0  ! mass of Sol in  earth masses
c      Msolkg = 1.98892 d30   ! mass of Sol in kg
      kmperau = 149 598 000.0 d0 ! km per au
      Mearth = 5.9742 d24    ! mass of Earth in kg
c     check mass of sun & Jupiter
c      print *, 'Msol, Msolkg, Mearth, Msol*Mearth, mjup/msol'
c      print *, Msol,Msolkg, Mearth, Msol*Mearth, 
c     * (Mjup*Mearth)/(Msol*Mearth)
c=====================================================
c     default input parameters
c      Mplanet = 300d0       ! planet mass in Earth masses 
c      Aplanet = 1.0d0      ! au
c      Mstar   = 1.0d0*Msol  ! Star mass
c=====================================================

c     hill radius = a(1-e)* (m/3M)^(1/3)
c     looks ok for relationship of things within the radius
c     like orbits of moons,
c     but 1+e is more appropriate for orbital interference, I think.

C     Hill radius of planet (max moon distance in au)
      Hplanet= 
     * Aplanet*(Mplanet/(3.0d0*Mstar*Msol))**(1.0d0/3.0d0) 
c      print *,'Aplanet,Mplanet,Mstar,Msol',Aplanet,Mplanet,Mstar,Msol
c      print *,'Planet Hill R (AU) = ',Hplanet
      Hplanet = kmperau * Hplanet
c      print *,'Planet Hill R (km) = ',Hplanet
c      print *,'Hplanet= ',Hplanet

c     not stable unless within 1/3 of hill radius per wikipedia
c     (also more aesthetic)
      Hplanet = Hplanet/3.0d0

      Am(1) = Hplanet ! initial maximum radius for placing moons

c      call draw_hill(Nameplanet,Hplanet)

c     moon parameters
c     total mass of all moons = 1.0-3.0 e-4  of planet
c     Ref: Canup and Ward (2006) 
c     A common mass scaling for satellite systems of gaseous planets. 
c     Nature, 441: 834-839.
c     see also: 
c http://phl.upr.edu/library/notes/themassandradiusofpotentialexomoons
c
c      rm = (1.0d-4) + (1.0d-4)*rgauss(1.0d0)
c      rm = 1.5d-4

      rm = (1.1d0 +1.4d0*randf())/10 000.0d0 ! 1.10

      Mtot = rm *Mplanet    ! in units of earth mass
      Mmin = Mtot/1 000 000.0d0      ! no smaller than 1/1 000 000 of total mass

c ------------------------------------------------------------------

c     planet radius in km
c     radius peaks at 1.65 x Mjup = 1.051 * Rjup
c     graph has min at 6Mjup
c     Ref: Giant Planet Interior Structure and Thermal Evolution
c          Fortney et al. (2009), Fig. 4

c      print *, ' '
c      if (Mplanet .le. 0.25d0*Mjup) then
c     it's rocky
c         print *, 'This planet is rocky.'
c         Rplanet = ((Mplanet/Mjup)**0.333d0)*Rjup
c      elseif (Mplanet .le. 1.65d0*Mjup) then
c     assume it's a gas giant
c         print *, 'This planet is a gas giant.'
c         Rplanet = ((Mplanet/Mjup)**0.10d0)*Rjup
c      elseif (Mplanet.le. 6.04d0*Mjup) then
c     it's a brown dwarf
c         print *, 'This "planet" is a brown dwarf.'
c         Rplanet = ((Mplanet/Mjup)**(-0.125d0))*Rjup
c      else
c     It's a star
c         print *, 'This "planet" is a dim star.'
c         Rplanet = 0.799d0*Rjup + (Mplanet-(6.04d0*Mjup))*Rjup
c         if (Rplanet.gt.10.0d0*Rjup) then
c         print *, 'Radius = ',Rplanet,' km = ',Rplanet/Rjup,' x Jup.'
c            print *, 'This "planet" is too large and massive: '
c            print *, ' Hill radius calculations fail.'
c            print *, 'Please use StarGen instead.'
c            stop
c         endif
c      endif
c      print *, 'Radius = ',Rplanet,' km = ',Rplanet/Rjup,' x Jup.'

c     Density of planet (for Roche Limit calculation)
c     mass = density * volume
c     density = mass/volume
C     Volume = 4/3 pi r^3
c     density = mass/ (4.0/3.0* pi *r**3)
c
c     but need to get units right......
c     density of water = 1 g/cm^3 = 1 kg / m^3 
c     1 km^3 = 1E6 m^3

      Vplanet = (4.0d0/3.0d0)*3.14159265d0*Rplanet**3 !km^3
      Dplanet = (Mearth* Mplanet) /  Vplanet  ! kg/km^3
c      scale:
c     1000 grams/kg = 1d3
c     1000x1000x1000 meters^3/km^3 = 1d9
c     100x100x100 cc / m^3 = 1d6
      Dplanet = Dplanet *(1d3/(1d6*1d9)) ! g/cc

c     jupiter's radius = ~70 000 km
c     metis (innermost moon): 128 000 km (1.8x planet's radius)
c     so make innermost orbit 1.5x planet's radius

      Amin= 1.5d0* Rplanet

      Am(0)=Amin  ! initial minimum radius for placing moons

c      print *, 'Rplanet,Am(0),Am(1) = ',Rplanet,Am(0),Am(1)

c     include dummy planet specs if appropriate
      if (Nameplanet.eq.'TestPlanet') then
         call write_planet(Nameplanet,Namestar,Rplanet,Aplanet,Mplanet)
      endif

c     random orbit radii out to hill radius of planet vs its sun
c     (rocky moon orbiting gas giant: roche limit is inside planet)

c     but put no moons within some multiple of hill radius of each other

c     specify masses in terms of earth mass
c     convert to kg later

      Mremaining = Mtot
      Nmoon = 0
      Ntest = 0

 100  continue
      Ntest = Ntest+1
!      print *,' Ntest=',Ntest
c      if (Ntest.gt.10) stop

c     quit if we've run out of mass 
c     or if the specified number of moons have been created

!      print *, Mremaining, ' remaining: ',100*Mremaining/Mtot,'%'
      if (Mremaining.lt.Mmin) then
         print *, 'Available mass exhausted'
         print *, 'after generating ',Nmoon,' moons.'
      endif
      if (Mremaining.lt.Mmin .or.Nmoon.ge. Nmoons) goto 200

c     select mass of this moon:
c     a random fraction of remaining mass

      r1 = randf()
c      r2 = 1.0d0- LOG10(1.0d0+9.0d0*r1)
      maxln = exp(1.0d0)
      r2 =  LOG(1.0d0+maxln*r1)/1.33d0
c      print *,'r2= ',r2
      Mmoon = r2 *Mremaining
      Mremaining = Mremaining - Mmoon

c      print *, 'Mmoon = ', Mmoon,' (mass)'

c      print *, 'placing moon'
c     insert this moon among the others
      call place_moon(Am,Hm,mmp1,
     * Nmoon,Amoon,Mmoon,Mtot,Mplanet)
c      print *, 'placed moon'
c      if (Ntest.gt.5) stop 'Ntest>5'
      
c     add to mass distribution
      i =  int(Mmoon* (10d0/Mtot))
      IF (i.lt.1) i=0
      if (i.ge.11) i=11
      masses(i)=masses(i)+1

c     and write to ssc file (with some other variables)
      call write_moon 
     * (Nmoon,Amoon,Mmoon,Mtot,
     * Mplanet,Rplanet,Dplanet,Hplanet,Aplanet,
     * Nameplanet, NameStar)
c      print *, 'wrote moon'
      goto 100
 200  continue

      print *, ' '
      PRINT '(a,12i4)', ' Mass distribution: ',(MASSES(I),I=0,11)

      call str_len(FileName,npc)
      print *,' Done: ',Nmoon,' moons in ',
     * 'Moons_'//FileName(:npc)//'.ssc'
      print *,'==================================='
      print *, ' '
      close (1)
      end
c-----------------------------------------------------
      subroutine draw_hill(Nameplanet,Hplanet)
      character*20 nameplanet
      double precision Hplanet
      call str_len(nameplanet,npl)
      write (1,*) '"HillRadius" "Sol/',Nameplanet(:npl),'"'
      write (1,*) '{'
      write (1,*) ' Class "moon"'
      write (1,*) ' Radius 1000'
      write (1,*) ' Color [ 1 0 0 ]'
      write (1,*) ' EllipticalOrbit '
      write (1,*) ' {'
      write (1,*) '   Period 1000'
      write (1,*) '   SemiMajorAxis ',Hplanet
      write (1,*) ' }'
      write (1,*) '}'
      write (1,*) ' '

      RETURN
      END


C===========================
c     write this moon to the ssc file
c     after determining its other parameters

      subroutine write_moon 
     * (Nmoon,Amoon,Mmoon,Mtot,
     * Mplanet,Rplanet,Dplanet,Hplanet,Aplanet,
     * Nameplanet, NameStar)

      implicit double precision (a-z)
      integer Nmoon,npc,nsc,nch
      character*20 Nameplanet,Namestar,Tmoon
      character*13 color
      logical lsphere

c     derive period

c     calculate appropriate gravitational constant
c     from the Moon's orbit around the Earth
      AM = 384748d0       ! semi-major axis in km
      PM = 27.32166155d0  ! sidereal period in days
      MM = 0.0123000383d0 !fraction of Earth's mass
      K = (PM**2) / ((AM**3)/(1.0d0+MM)) 
c      print *,' K= ',K

c      print *, 'Nmoon,Amoon,Mmoon,Mplanet,Aplanet,Dplanet = '
c      print *, Nmoon,Amoon,Mmoon,Mplanet,Aplanet,Dplanet

c     derive period, ignoring moon's mass
C     p^2 = K a^3/m
c     moon's period: K (above) SMA (km, provided) Mplanet (earths, provided)
      Pmoon = sqrt(K* Amoon**3/Mplanet)

c     random composition (density)
c     Ramdom density 1-5: ice to metal
c     except that the farther out a planet is,
c     the lower the density should be (more ices, less metals)

c     my guess:
c     most likely density = 1.0 for outer planet
c     most likely density = 3.3 for inner planet

c     fractional range of planetary distances:
c     limit planet SMA distance to 40 au
      Ap = min(Aplanet,40.0d0)
c     and discover its fractional distance
      den = (40.0d0-Ap)/15.0d0
c      print *, ' den = ',den

c     (approximate poisson distribution)
      x1 = rgauss (0.54d0)
c      print *, x1,x2
      IF (x1.lt.0.0d0) X1=-X1

      Dmoon = 0.90d0+den*X1
c      print *, 'Dmoon = ',Dmoon
c     heck with it: limit max density
      if (Dmoon.gt.3.3d0) Dmoon = 3.3d0

c      Dmoon = 1.0d0+randf()*4.0d0  ! g/cm^3

C     calculate roche limit for moon:
c     generate rings instead of moon
c     if an icy moon is inside its roche limit
c
      d = 2.423d0* Rplanet*(2d0*Dplanet/Dmoon)**(1d0/3d0)
c      print *,'Dmoon, d, Amoon, diff = ',Dmoon,d,Amoon, Amoon-d

c     but not yet
      if (Amoon .lt. d .and. Dmoon .lt. 1.2d0) then
         print *, 'Rings! (but not yet)'
      endif

c     Mass as multiple of Earth's mass
c     Density in g/cc 
c     returns Radius in km
      call Radius_moon(Mmoon,Dmoon,Rmoon)

c     color depends on composition, too
      if (Dmoon.lt.2.0d0) then
         color = '[0.8 0.8 0.8]'
      elseif (Dmoon.lt.3.5d0) then
         color = '[0.5 0.4 0.3]'
      else
         color = '[0.3 0.4 0.5]'
      endif

c     as does the albedo
      Albedo = 0.2d0/Dmoon

      Mearth = 5.9742d24    ! earth mass in kg
      Kgmoon = Mmoon*Mearth


c     and whether it's spherical due to hydrostatic equilibrium
c     BUT function isn't entirely obvious
c     250km is close enough for moons of Saturn *shrug*

      if (Rmoon.lt.250d0) then
         lsphere = .false.
      else 
         lsphere=.true.
      endif

c     randomized orbital parameters
c     probably should have some relationships with each other
c     (resonances)
c     but not now.

c     Inclination
c       probably larger with larger distances

c     probably inversely proportional to cube of distance
c     due to tidal effects
c     BUT that expands much too fast
      fdist = Amoon/Hplanet

c     and larger with smaller masses?
c     also expands much too fast
c      fmass =  Mtot/Mmoon
      fmass =  (Mtot/Mmoon)**0.2d0

c     and larger with smaller oblateness of planet
c     but dunno what the oblateness is

      ri=rgauss(1.0d0)
      Imoon = fdist*fmass*ri

c     Eccentricity 
c      major moons <0.01. more distant minor can be larger.
      Emoon = 0.01d0*randf()

c     ArgOfPericenter
      AOPmoon = 360.0d0*randf()
c     AscendingNode
      ANmoon = 360.0d0*randf()
c     MeanAnomaly
      MAmoon = 360.0d0*randf()

c     Rotational parameters are omitted
c     thus causing all moons to be tidally locked

c     atmospheric parameters are omitted for smaller moons
c     included if mass & density .ge. titan. see below

      call str_len(Nameplanet, npc)
      call str_len(Namestar, nsc)
c     replace underscores by spaces in star name
      call u2sp(Namestar)

      call left_justify(Nmoon,Tmoon,nch)

      write (1,*) '"'//Nameplanet(:npc)//'_Moon ',Tmoon(:nch),'" "',
     * Namestar(:nsc)//'/'//NamePlanet(:npc)//'"'

      write (1,*) '{'
      write (1,*) ' Class "moon"'
      write (1,fmt='(a,e50.32,a,1p,e50.32,a)')
     *  '   # mass  = ',Mmoon,' x Earth = ',Kgmoon,' kg'
      write (1,fmt='(a,f6.3)') '   # density = ',Dmoon
      if (Mmoon.gt. 0.75d0) then !1.11
         print *, ' Earthlike moon?'
         write(1,*) '# Earthlike?'
         endif

      write (1,fmt='(a,f10.3)')'  Radius ',Rmoon

      IF (.NOT. lsphere) write(1,*) ' Mesh "asteroid.cms"'

      if (Dmoon.lt.1.0d0) then
         write (1,*) ' Texture "tethys.*"'
      elseif (Dmoon.lt.1.5d0) then
         write (1,*) ' Texture "enceladus.*"'
      elseif (Dmoon.lt.2.5d0) then
         write (1,*) ' Texture "callisto.*"'
      elseif (Dmoon.lt.3.5d0) then
         write (1,*) ' Texture "ganymede.*"'
      else
         write (1,*) ' Texture "europa.*"'
      endif

      write (1,*) ' Color '//color ! 1.14
      write (1,*) ' BlendTexture true'

      write (1,*) ' EllipticalOrbit '
      write (1,*) ' {'
      write (1,fmt='(a,f10.4)') '   Period          ',Pmoon
      write (1,fmt='(a,f50.32)') '   SemiMajorAxis ',Amoon
      write (1,fmt='(a,f48.32)') '   Eccentricity    ',Emoon
      write (1,fmt='(a,f48.32)')
     * '   Inclination     ',Imoon!,' # ',fdist,fmass,ri
      write (1,fmt='(a,f48.32)') '   ArgOfPericenter ',AOPmoon
      write (1,fmt='(a,f48.32)') '   AscendingNode   ',ANmoon
      write (1,fmt='(a,f48.32)') '   MeanAnomaly     ',MAmoon
      write (1,*) ' }'

c     all moons are assumed to be tidally locked to the planet
c     hence no rotation specificiation

c     include atmosphere if mass & density >= titan
      if (Kgmoon .gt. 1.3d23 .and. Dmoon .gt. 1.8d0) then
c       duplicate Titan's atmosphere for now
         write (1,*) '    Atmosphere {'
         write (1,*) '      Height         500.0'
         write (1,*) '      Lower      [ 0.477 0.367 0.211 ]'
         write (1,*) '	    Upper      [ 0.96 0.805 0.461 ]'
         write (1,*) '	    Sky        [ 0.3 0 0 ]'
         write (1,*) '      Mie              0.0001'
         write (1,*) '      MieAsymmetry    -0.55'
         write (1,*) '      Rayleigh   [ 0.0 0.0 0.00017 ]'
         write (1,*) '      Absorption [ 0.000075 0.00030 0.00025 ]'
         write (1,*) '      MieScaleHeight 220.0 '
         write (1,*) '      }'
      endif


      write (1,fmt='(a,f6.3)') ' Albedo ',Albedo
      write (1,*) '}'
      write (1,*) ' '

      return
      end

c==============================================================
      subroutine Radius_moon ( Mmoon,Dmoon, Rmoon)
c     calculate radius (depends on composition)
c     volume = mass/density = 4/3 pi R^3
c     r^3 = (3/4)*(mass/density)/pi
c     radius = (0.75d0/3.14159264d0*(mass/density))**(1/3)
c     needs to be in km
c
c     verified with moons of Jupiter & Saturn
c     max deviation = 0.3% (0.003x)

      implicit double precision (a-z)

      k = 0.75d0/3.14159264d0

      Mearth = 5.9742 d27    ! mass of Earth in grams
      Mmoon_in_g = Mmoon*Mearth
      volume = Mmoon_in_g /Dmoon
c      print *, 'Mmmon = ',Mmoon_in_g,' grams, Dmoon = ',Dmoon
c      print *, 'volume= ',volume
      Rmoon = (k*volume)**0.3333333333333333333d0
c      print *, 'Rmoon = ',Rmoon
      Rmoon = Rmoon/(100.0d0 * 1000.0d0) ! cm -> m, m -> km
c      print *, 'Rmoon = ',Rmoon
      return
      end
c==============================================================


      subroutine get_args
     * (FileName,Nameplanet,Mplanet,Rplanet,Aplanet, NameStar,Mstar,
     *  Nmoons,version)

      implicit double precision (a-z)
      integer nf,Nmoons,iseed,na,lt,ln
      character*20 Nameplanet,Massplanet,SMAplanet,MassStar,NumMoons
      character*20 NameStar,RanSeed,tmp,FileName
      character*20 Radiusplanet
      character*5 version
      character*2 flg
      character*1 char
      logical Lname,Lmp,Lsmap,Lmstar,Lseed,Lnum,Lnstar,Lfn,Lrad
      data Lname,Lmp,Lsmap,Lmstar,Lseed,Lnum,Lnstar,Lfn,Lrad /9*.false./

c     -a planet sma
c     -n planet name
c     -N number of moons
c     -m planet mass
c     -R planet radius
c     -M star mass
c     -s seed for ran
c     -S star name

c     default input parameters
      Msol = 332 918.215d0  ! earth masses
      Mplanet = 300d0       ! planet mass in Earth masses 
      Aplanet = 1.0d0      ! au
      Mstar   = 1.0d0*Msol  ! Star mass
      Rplanet = 1.0d0
c     used to calculate default radius
      Mjup = 317.82 d0
      Rjup = 71 492.0 d0
c=====================================================

      print *, ' moon_orbits '//version

      do nf = 1,16,2
         call getarg(nf,flg)
         if     (flg.eq.'-a') then
            call getarg(nf+1, SMAplanet)
            Lsmap=.true.
         elseif (flg.eq.'-F') then
            call getarg(nf+1, FileName)
            Lfn = .true.
         elseif (flg.eq.'-m') then
            call getarg(nf+1, MassPlanet)
            Lmp = .true.
         elseif (flg.eq.'-R') then
            call getarg(nf+1, RadiusPlanet)
            Lrad=.true.
         elseif (flg.eq.'-M') then
            call getarg(nf+1, MassStar)
            Lmstar=.true.
         elseif   (flg.eq.'-n') then
            call getarg(nf+1, Nameplanet)
            Lname = .true.
         elseif   (flg.eq.'-N') then
            call getarg(nf+1, NumMoons)
            Lnum = .true.
         elseif   (flg.eq.'-s') then
            call getarg(nf+1, RanSeed)
            Lseed=.true.
         elseif   (flg.eq.'-S') then
            call getarg(nf+1, NameStar)
c     assume it has several parts (and is last on line)
            do na =2,4
               call getarg(nf+na, tmp)
               if (tmp.ne.' ' .and. tmp(1:1).ne.'-'
     *              .and.tmp(1:1).ne.char(13)) then
                  call str_len(tmp,lt)
                  if (lt.gt.0) then
                     call str_len(NameStar,ln)
                     NameStar(ln+1:)='_'//tmp
                  endif
               endif
            enddo
            Lnstar=.true.
            goto 13
         else 
            if (flg.eq.' ') goto 13
            print *, 'Unrecognized option: ',flg
            print *, ' '

        print *, ' moon_orbits '//version
        print *, '  generates SSC for major moons of a gas giant'
        print *, ' '
        print *, '  put a space between the option flag and its value'
	print *, ' -a planet_sma (in AU; default = 5.0)'
	print *, ' -F file name (not extension)'
	print *, ' -m planet_mass (as fraction of Earth; default=300.0)'
	print *, ' -R planet radius (in km)'
	print *, ' -M star_mass (as fraction of Sun; default = 1.0)'
	print *, ' -n planet_name (max 20 chars; default = TestPlanet )'
	print *, ' -N number_of_moons (default = 10)'
	print *, ' -s seed (for random number generator; def=14159262)'
	print *, ' -S star_name (max 20 chars; default = Sol)'
        stop
         endif

      enddo
 13   continue

      if (Lname) then
         print *, 'Planet name = ',Nameplanet
      else
         Nameplanet = 'TestPlanet'
         print *, 'Planet name (-n) not specified, using ',Nameplanet
         print *, ' (Including dummy planet definition in ssc.)'
      endif


      if (Lmp) then
         print *, 'Planet mass = ',MassPlanet
         call fix_float(MassPlanet)
      else
         MassPlanet = '300.0'
         print *, 'Planet mass (-m) not specified, using ',MassPlanet
      endif

      read(MassPlanet,fmt='(d20.10)') Mplanet

      if (Lrad) then
	 print *, 'Planet radius = ',RadiusPlanet
	 call fix_float(RadiusPlanet)
	 read(RadiusPlanet,fmt='(d20.10)') Rplanet
      else
         print *, ' '
	 if (Mplanet .le. 0.25d0*Mjup) then 
	    print *, 'This planet is rocky.'
	    Rplanet = ((Mplanet/Mjup)**0.333d0)*Rjup
	 elseif (Mplanet .le. 1.65d0*Mjup) then
	    print *, 'This planet is a gas giant.'
	    Rplanet = ((Mplanet/Mjup)**0.10d0)*Rjup
	 elseif (Mplanet.le. 6.04d0*Mjup) then
	    print *, 'This "planet" is a brown dwarf.'
	    Rplanet = ((Mplanet/Mjup)**(-0.125d0))*Rjup
	 else
	    print *, 'This "planet" is a dim star.'
	    Rplanet = 0.799d0*Rjup + (Mplanet-(6.04d0*Mjup))*Rjup
	    if (Rplanet.gt.10.0d0*Rjup) then
	      print *, 'Radius = ',Rplanet,' km = ',Rplanet/Rjup,' x Jup.'
	      print *, 'This "planet" is too large and massive: '
	      print *, ' Hill radius calculations fail.'
	      print *, 'Please use StarGen instead.'
	      stop
	    endif
	 endif
	 print *, 'Planet radius = ',Rplanet
      endif


      if (Lsmap) then
         print *, 'Planet SMA = ',SMAplanet
         call fix_float(SMAPlanet)
      else
         SMAPlanet = '5.0'
         print *, 'Planet SMA (-a) not specified, using ',SMAPlanet
      endif

      if (Lnstar) then
         print *, 'Star name = ',NameStar
      else
         NameStar = 'Sol'
         print *, 'Star name (-S) not specified, using ',NameStar
      endif

      if (Lmstar) then
         print *, 'Star mass = ',MassStar
         call fix_float(MassStar)
      else
         MassStar = '1.0'
         print *, 'Star mass (-M) not specified, using ',MassStar
      endif

      if (Lseed) then
         print *, 'Random seed = ',RanSeed
         call fix_float(RanSeed)
      else
         RanSeed = '14159262.0'
         print *, 'Seed (-s) not specified, using ',RanSeed
      endif

      if (Lnum) then
         print *, 'Number of Moons = ',NumMoons
         call fix_float(NumMoons)
      else
         NumMoons = '10.0'
         print *, 'Number of moons (-N) not specified, using ',NumMoons
      endif

      if (Lfn) then
         print *, 'File name = ',FileName
      else
         call str_len(NameStar,ln)
         FileName = NameStar(:ln)//'_'//Nameplanet
         print *, 'File name (-F) not specified, using ',FileName
      endif

c     translate ascii values into appropriate numbers

      read(NumMoons,fmt='(d20.10)') FNmoons
      Nmoons = int(fnmoons)

      read(MassPlanet,fmt='(d20.10)') Mplanet
      read(MassStar,fmt='(d20.10)') Mstar
      read(SMAPlanet,fmt='(d20.10)') Aplanet

      read(RanSeed,fmt='(d20.10)') Dseed
      iseed = int(Dseed)
      call srandf(iseed)

      return

      END
c-----------------------------------------------------
      subroutine fix_float(a0)
c     ensure a decimal point in number
      character*20 a0
      
      npd = index(a0,'.')
      if (npd.ne.0) return

      npe = index(a0,'e')
      if (npe.eq.0)  npe = index(a0,'E')
      if (npe.eq.0)  npe = index(a0,'d')
      if (npe.eq.0)  npe = index(a0,'D')
         
      if (npe.eq.0) then
         call str_len(a0,np)
         a0(np+1:np+2)='.0'
         return
      else
         a0=a0(:npe-1)//'.0'//a0(npe:)
      endif
      return
      end
c-----------------------------------------------------
      subroutine str_len(str,ncf)
      character*(*) str
      lens = len(str)
      do nc = lens,1,-1
         if (str(nc:nc).ne. ' ') then
            ncf = nc
            return
         endif
      enddo
      ncf = 1
      return
      end
c=============================================================
      SUBROUTINE SRANDf(ISEED)
C
C  This subroutine sets the integer seed to be used with the
C  companion RAND function to the value of ISEED.  A flag is 
C  set to indicate that the sequence of pseudo-random numbers 
C  for the specified seed should start from the beginning.
C
      COMMON /SEED/JSEED,IFRST
C
      JSEED = ISEED
      IFRST = 0
C
      RETURN
      END
c------------------------

      double precision FUNCTION RANDf()
C
C  This function returns a pseudo-random number for each invocation.
C  It is a FORTRAN 77 adaptation of the "Integer Version 2" minimal 
C  standard number generator whose Pascal code appears in the article:
C
C     Park, Steven K. and Miller, Keith W., "Random Number Generators: 
C     Good Ones are Hard to Find", Communications of the ACM, 
C     October, 1988.
C
      PARAMETER (MPLIER=16807,MODLUS=2147483647,MOBYMP=127773,
     +           MOMDMP=2836)
C
      COMMON  /SEED/JSEED,IFRST
      INTEGER HVLUE, LVLUE, TESTV, NEXTN
      SAVE    NEXTN
C
      IF (IFRST .EQ. 0) THEN
        NEXTN = JSEED
        IFRST = 1
      ENDIF
C
      HVLUE = NEXTN / MOBYMP
      LVLUE = MOD(NEXTN, MOBYMP)
      TESTV = MPLIER*LVLUE - MOMDMP*HVLUE
      IF (TESTV .GT. 0) THEN
        NEXTN = TESTV
      ELSE
        NEXTN = TESTV + MODLUS
      ENDIF
      RANDf = dble(NEXTN)/dble(MODLUS)
C
      RETURN
      END
      BLOCKDATA RANDBD
      COMMON /SEED/JSEED,IFRST
C
      DATA JSEED,IFRST/123456789,0/
C
      END

!****************************************************************************
! RGAUSS
! PURPOSE: generate gaussian random numbers with given sigma
! Uses FUNCTION RANDF() to generate uniform random numbers between 0 and 1
! Uses the Box-Muller algorithm to generate numbers with
! a Gaussian distribution of probability.
!

      double precision function rgauss(sigma)
      real*8 x1, x2, w, y1, sigma,randf

 100  continue
         x1 = 2.0d0 * randf() - 1.0d0
         x2 = 2.0d0 * randf() - 1.0d0
         w = x1 * x1 + x2 * x2
c     print *,'x1,x2, w = ',x1,x2,w
      if ( (w .ge. 1.0d0).or.(w.eq.0.0d0) ) goto 100

      w = sigma*sqrt( (-2.0d0 * log( w ) ) / w )
c      print *,' w2 = ',w
      y1 = x1 * w
c      y2 = x2 * w
      rgauss = y1
      return
      end
c===========================================
      subroutine u2sp(Namestar)
c     restore spaces in star name
      character*20 Namestar
      do nc = 1,20
         if (Namestar(nc:nc).eq.'_') Namestar(nc:nc)=' '
      enddo

      return
      end
c===========================================
      subroutine left_justify(number,string,nch)
c     left justifies number in string

      integer number,nch,ns,nsp
      character*20 string
      
      write(unit=string,fmt=*) number

c     eliminate leading spaces
      do ns = 1,20
         if (string(ns:ns).ne.' ') then
            nsp = ns
            goto 10
         endif
      enddo
 10   continue
      if (nsp.ge.1) string = string(nsp:)

c     eliminate trailing spaces
      do ns = 1,20
         if (string(ns:ns).eq.' ') then
            nch = ns-1
            goto 20
         endif
      enddo
 20   continue
c      print *, string, nsp,nch
      return
      end


c=================================================

      subroutine place_moon(Am,Hm,mmp1,
     * Nmoon,Amoon,Mmoon,Mtot,Mplanet)

      implicit double precision (a-z)
      integer mmp1,Nmoon,nm,MoonThis
      dimension Am(0:mmp1),Hm(0:mmp1)

c      print *, 'place_moon: Nmoon, am0,am1,hm0,hm1=',
c     * Nmoon,am(0),am(1),hm(0),hm(1)
c      stop

c    Note:
c     hill radius = a(1-e)* (m/3M)^(1/3)
c     greater eccentricity shrinks the hill radius
c      which is OK for stability of orbits within the hill radius
c      but the opposite seems more appropriate for
c      orbital interference; max e is 1 so use that

c     select a region within which another moon can be placed
c     (in between mimimum radius, existing moons, and max radius)
c     assumes moons are indexed in order of increasing sma

c     treat first moon as special case
      if (Nmoon.lt.1) then
         r1 = Am(0)
         r2 = Am(1)
         Amoon = r1+(r2-r1)*randf()
         nm = 1
         Hmoon = Amoon*2.0d0
     *            *((Mmoon/(3.0d0*Mplanet))**(1.0d0/3.0d0))

         MoonThis = 1
         Am(MoonThis) = Amoon
         Hm(MoonThis) = Hmoon

         am(2) = r2

         Nmoon = 1
c         do i=0,2
c          print *, 'am(',i,') = ',am(i)
c         enddo

         return
      else

c    the probability that it's in a given interval is 
c     proportional to the size of that interval
         probmax = 0.0d0

c     there's one more interval available than there are moons
         do nm = 1,Nmoon+1

c innermost sma = inner moon+ its hill radius+ this moon's hill radius
            Hmoon = Am(nm-1)*2.0d0
     *            *((Mmoon/(3.0d0*Mplanet))**(1.0d0/3.0d0))
            r1 = Am(nm-1)+Hm(nm-1) +Hmoon
c            print *,  'nm,Am(nm-1),Hm(nm-1),Am(nm-1)+Hm(nm-1)=',
c     * nm,Am(nm-1),Hm(nm-1),Am(nm-1)+Hm(nm-1)
c            print *, 'Hmoon,r1=',Hmoon,r1

c outermost sma = outer moon - its hill radius - this moon's hill radius
            Hmoon = Am(nm)*2.0d0
     *            *((Mmoon/(3.0d0*Mplanet))**(1.0d0/3.0d0))
            r2 = Am(nm)-Hm(nm) -Hmoon
c            print *,  '        nm,Am(nm),Hm(nm),Am(nm)-Hm(nm)=',
c     * nm,Am(nm),Hm(nm),Am(nm)-Hm(nm)
c            print *, 'Hmoon,r2=',Hmoon,r2
c     more likely to place moon in largest interval
            prob = (r2-r1)*randf()
c            print *,' prob=',prob

            if (prob.gt.probmax) then
               probmax = prob
               Amoon = r1+(r2-r1)*randf() !1.09
               MoonThis = nm
            endif
         enddo
      endif

      Hmoon = Amoon*2.0d0
     *            *((Mmoon/(3.0d0*Mplanet))**(1.0d0/3.0d0))


c     one more moon orbiting
      Nmoon=Nmoon+1
c     Move all exterior moons (including max planetary hill radius)
      do nm = Nmoon+1,MoonThis+1,-1
         Am(nm) = Am(nm-1)
         Hm(nm) = Hm(nm-1)
      enddo
c     and insert this moon
      Am(MoonThis) = Amoon
      Hm(MoonThis) = Hmoon

c      do i=0,Nmoon+1
c         print *, Nmoon, MoonThis,i, Am(i),Hm(i)
c      enddo
c      if (MoonThis.gt.2) stop

      return
      end
c===================================
         subroutine write_planet
     *     (Nameplanet,Namestar,Rplanet,Aplanet,Mplanet)

         double precision Rplanet,Aplanet,Mplanet,Mjup
         character*20 Nameplanet,Namestar

         call str_len(nameplanet,npl)
         call str_len(namestar,nst)

         write(1,*) '# dummy planet for testing'
         write(1,*) '"'//nameplanet(:npl)//'" "'//namestar(:nst)//'"'
         write(1,*) '{'

      Mjup = 317.82 d0       ! mass of Jupiter in earth masses
      if (Mplanet .le. 0.25d0*Mjup) then
c     it's rocky
         write(1,*) '  Texture "asteroid.*"'
      elseif (Mplanet .le. 1.65d0*Mjup) then
c     assume it's a gas giant
         write(1,*) '  Texture "exo-class1.*"'
      elseif (Mplanet.le. 6.04d0*Mjup) then
c     it's a brown dwarf
         write(1,*) '  Texture "browndwarf.*"'
      else
c     It's a star
         write(1,*) '  Texture "mstar.*"'
         write(1,*) '  Emissive true'
      endif


         write(1,fmt='(a,f15.1)') '   Radius ',Rplanet
         write(1,*) '  Oblateness 0.05'
         write(1,*) '  EllipticalOrbit { '
         write(1,fmt='(a,f15.1)') '     SemiMajorAxis ',Aplanet
         write(1,*) '    Period 10 }'
         write(1,*) '  UniformRotation { Period 12 Inclination 4}'
         write(1,*) '  Albedo 0.5'
         write(1,*) '}'
         return
         end