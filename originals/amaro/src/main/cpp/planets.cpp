#include "planets.h"
#include "const.h"

planet *luna = NULL;
planet *callisto = NULL;
planet *ganymede = NULL;
planet *europa = NULL;
planet *io = NULL;
planet *iapetus = NULL;
planet *hyperion = NULL;
planet *titan = NULL;
planet *rhea = NULL;
planet *dione = NULL;
planet *tethys = NULL;
planet *triton = NULL;
planet *charon = NULL;

planet *jeraddo = NULL;
planet *derna = NULL;
planet *bajorVII1 = NULL;
planet *bajorVII2 = NULL;
planet *bajorVII3 = NULL;
planet *bajorVIII1 = NULL;
planet *bajorVIII2 = NULL;

planet *eris = NULL;
planet *pluto = NULL;
planet *neptune = NULL;
planet *uranus = NULL;
planet *saturn = NULL;
planet *jupiter = NULL;
planet *ceres = NULL;
planet *mars = NULL;
planet *earth = NULL;
planet *venus = NULL;
planet *mercury = NULL;
  
planet *eriEpsI = NULL;
planet *UMa47III = NULL;
planet *UMa47II = NULL;
planet *UMa47I = NULL;
planet *horIotI = NULL;
planet *xiumaab = NULL;
planet *xiumabb = NULL;
planet *Bellerophon = NULL;
planet *can55d = NULL;
planet *can55f = NULL;
planet *can55c = NULL;
planet *can55b = NULL;
planet *can55e = NULL;
planet *UPSAndAe = NULL;
planet *UPSAndAd = NULL;
planet *UPSAndAc = NULL;
planet *UPSAndAb = NULL;
planet *hd10180h = NULL;
planet *hd10180g = NULL;
planet *hd10180f = NULL;
planet *hd10180j = NULL;
planet *hd10180e = NULL;
planet *hd10180d = NULL;
planet *hd10180i = NULL;
planet *hd10180c = NULL;
planet *hd10180b = NULL;
planet *gliese581f = NULL;
planet *gliese581d = NULL;
planet *gliese581g = NULL;
planet *gliese581c = NULL;
planet *gliese581b = NULL;
planet *gliese581e = NULL;
planet *hd10647b = NULL;
planet *leo83Bb = NULL;
planet *leo83Ba = NULL;
planet *muarie = NULL;
planet *muarib = NULL;
planet *muarid = NULL;
planet *muaric = NULL;
planet *hd28185b = NULL;
planet *hd40307g = NULL;
planet *hd40307f = NULL;
planet *hd40307e = NULL;
planet *hd40307d = NULL;
planet *hd40307c = NULL;
planet *hd40307b = NULL;
planet *kepler22b = NULL;
planet *taucetf = NULL;
planet *taucete = NULL;
planet *taucetd = NULL;
planet *taucetc = NULL;
planet *taucetb = NULL;
planet *alfcentbb = NULL;
planet *EPSErib = NULL;
planet *EPSEric = NULL;
planet *cyteen = NULL;
planet *GL849b = NULL;
planet *ILAqrb = NULL;
planet *ILAqrc = NULL;
planet *ILAqrd = NULL;
planet *HD20794d = NULL;
planet *HD20794c = NULL;
planet *HD20794b = NULL;
planet *BETHyib = NULL;
planet *hd208527b = NULL;
planet *kepler11g = NULL;
planet *kepler11f = NULL;
planet *kepler11e = NULL;
planet *kepler11d = NULL;
planet *kepler11c = NULL;
planet *kepler11b = NULL;
planet *gliese667Cb = NULL;
planet *gliese667Cc = NULL;
planet *gliese667Cd = NULL;
planet *gliese667Ce = NULL;
planet *gliese667Cf = NULL;
planet *gliese667Cg = NULL;
planet *gliese667Ch = NULL;
planet *kepler283b = NULL;
planet *kepler283c = NULL;
planet *kepler62f = NULL;
planet *kepler62e = NULL;
planet *kepler62d = NULL;
planet *kepler62c = NULL;
planet *kepler62b = NULL;
planet *kepler296b = NULL;
planet *kepler296c = NULL;
planet *kepler296d = NULL;
planet *kepler296e = NULL;
planet *kepler296f = NULL;
planet *gliese180b = NULL;
planet *gliese180c = NULL;
planet *gliese163b = NULL;
planet *gliese163c = NULL;
planet *gliese163d = NULL;
planet *kepler61b = NULL;
planet *gliese422b = NULL;
planet *kepler298b = NULL;
planet *kepler298c = NULL;
planet *kepler298d = NULL;
planet *kepler174b = NULL;
planet *kepler174c = NULL;
planet *kepler174d = NULL;
planet *gliese682b = NULL;
planet *gliese682c = NULL;
planet *hd38529b = NULL;
planet *hd38529c = NULL;
planet *hd202206b = NULL;
planet *hd202206c = NULL;
planet *hd8673b = NULL;
planet *hd22781b = NULL;
planet *hd217786b = NULL;
planet *hd106270b = NULL;
planet *hd38801b = NULL;
planet *hd39091b = NULL;
planet *hd141937b = NULL;
planet *hd33564b = NULL;
planet *hd23596b = NULL;
planet *hd222582b = NULL;
planet *hd86264b = NULL;
planet *hd196067b = NULL;
planet *hd10697b = NULL;
planet *hd132406b = NULL;
planet *hd13908b = NULL;
planet *hd13908c = NULL;
planet *hd2039b = NULL;
planet *hd82943b = NULL;
planet *hd82943c = NULL;
planet *hd82943d = NULL;
planet *moa2011blg293lb = NULL;
planet *hd213240b = NULL;
planet *kepler186b = NULL;
planet *kepler186c = NULL;
planet *kepler186d = NULL;
planet *kepler186e = NULL;
planet *kepler186f = NULL;
planet *kapteynb = NULL;
planet *kapteync = NULL;

planet *bajorI = NULL;
planet *bajorII = NULL;
planet *bajorIII = NULL;
planet *bajorIV = NULL;
planet *bajorV = NULL;
planet *bajorVI = NULL;
planet *bajorVII = NULL;
planet *bajorVIII = NULL;
planet *bajorIX = NULL;
planet *bajorX = NULL;
planet *bajorXI = NULL;
planet *bajorXII = NULL;
planet *bajorXIII = NULL;
planet *bajorXIV = NULL;

void initPlanets()
{
  // moons in our solar system
  luna = new planet();
  luna->setPlanetNo(1);
  luna->setMoonA(2.571e-3);
  luna->setMoonE(0.055);
  luna->setAxialTilt(1.53);
  luna->setGasGiant(false);
  luna->setDustMass(EM(0.01229));
  luna->setDeletable(false);
  luna->reconnect_to = NULL;
  
  callisto = new planet();
  callisto->setPlanetNo(4);
  callisto->setMoonA(1.259e-2);
  callisto->setMoonE(0);
  callisto->setGasGiant(false);
  callisto->setDustMass(EM(1.62e-2));
  callisto->setDeletable(false);
  callisto->reconnect_to = NULL;
  
  ganymede = new planet();
  ganymede->setPlanetNo(3);
  ganymede->setMoonA(7.16e-3);
  ganymede->setMoonE(0.0796);
  ganymede->setGasGiant(false);
  ganymede->setDustMass(EM(2.6e-2));
  ganymede->next_planet = callisto;
  ganymede->setDeletable(false);
  ganymede->reconnect_to = callisto;
  
  europa = new planet();
  europa->setPlanetNo(2);
  europa->setMoonA(4.49e-3);
  europa->setMoonE(0.0075);
  europa->setGasGiant(false);
  europa->setDustMass(EM(7.9e-3));
  europa->next_planet = ganymede;
  europa->setDeletable(false);
  europa->reconnect_to = ganymede;
  
  io = new planet();
  io->setPlanetNo(1);
  io->setMoonA(2.82e-3);
  io->setMoonE(0.0006);
  io->setGasGiant(false);
  io->setDustMass(EM(1.21e-2));
  io->next_planet = europa;
  io->setDeletable(false);
  io->reconnect_to = europa;
  
  iapetus = new planet();
  iapetus->setPlanetNo(6);
  iapetus->setMoonA(2.38e-2);
  iapetus->setMoonE(0.029);
  iapetus->setGasGiant(false);
  iapetus->setDustMass(EM(8.4e-4));
  iapetus->setDeletable(false);
  iapetus->reconnect_to = NULL;
  
  hyperion = new planet();
  hyperion->setPlanetNo(5);
  hyperion->setMoonA(9.89e-3);
  hyperion->setMoonE(0.110);
  hyperion->setGasGiant(false);
  hyperion->setDustMass(EM(1.82e-5));
  hyperion->next_planet = iapetus;
  hyperion->setDeletable(false);
  hyperion->reconnect_to = iapetus;
  
  titan = new planet();
  titan->setPlanetNo(4);
  titan->setMoonA(8.17e-3);
  titan->setMoonE(0.0289);
  titan->setGasGiant(false);
  titan->setDustMass(EM(2.3e-2));
  titan->next_planet = hyperion;
  titan->setDeletable(false);
  titan->reconnect_to = hyperion;
  
  rhea = new planet();
  rhea->setPlanetNo(3);
  rhea->setMoonA(3.52e-3);
  rhea->setMoonE(0.0009);
  rhea->setGasGiant(false);
  rhea->setDustMass(EM(3.85e-4));
  rhea->next_planet = titan;
  rhea->setDeletable(false);
  rhea->reconnect_to = titan;
  
  dione = new planet();
  dione->setPlanetNo(2);
  dione->setMoonA(2.52e-3);
  dione->setMoonE(0.0021);
  dione->setGasGiant(false);
  dione->setDustMass(EM(1.74e-4));
  dione->next_planet = rhea;
  dione->setDeletable(false);
  dione->reconnect_to = rhea;
  
  tethys = new planet();
  tethys->setPlanetNo(1);
  tethys->setMoonA(1.97e-3);
  tethys->setMoonE(0);
  tethys->setGasGiant(false);
  tethys->setDustMass(EM(1.09e-4));
  tethys->next_planet = dione;
  tethys->setDeletable(false);
  tethys->reconnect_to = dione;

  triton = new planet();
  triton->setPlanetNo(1);
  triton->setMoonA(2.36e-3);
  triton->setMoonE(0);
  triton->setGasGiant(false);
  triton->setDustMass(EM(2.31e-2));
  triton->setDeletable(false);
  triton->reconnect_to = NULL;
  
  charon = new planet();
  charon->setPlanetNo(1);
  charon->setMoonA(1.31e-4);
  charon->setMoonE(0);
  charon->setGasGiant(false);
  charon->setDustMass(EM(2.54e-4));
  charon->setDeletable(false);
  charon->reconnect_to = NULL;
  
  // planets and dwarf planets in our solar system
  eris = new planet();
  eris->setPlanetNo(11);
  eris->setA(67.6681);
  eris->setE(0.44177);
  eris->setGasGiant(false);
  eris->setDustMass(EM(0.0025));
  
  pluto = new planet();
  pluto->setPlanetNo(10);
  pluto->setA(39.529);
  pluto->setE(0.248);
  pluto->setAxialTilt(122.5);
  pluto->setGasGiant(false);
  pluto->setDustMass(EM(0.002));
  pluto->first_moon = charon;
  pluto->next_planet = eris;
  pluto->first_moon_backup = charon;
  
  neptune = new planet();
  neptune->setPlanetNo(9);
  neptune->setA(30.061);
  neptune->setE(0.10);
  neptune->setAxialTilt(29.6);
  neptune->setGasGiant(true);
  neptune->setDustMass(EM(1.2));
  neptune->setGasMass(EM(17.14 - 1.2));
  neptune->first_moon = triton;
  neptune->next_planet = pluto;
  neptune->first_moon_backup = triton;
  
  uranus = new planet();
  uranus->setPlanetNo(8);
  uranus->setA(19.191);
  uranus->setE(0.046);
  uranus->setAxialTilt(97.9);
  uranus->setGasGiant(true);
  uranus->setDustMass(EM(1.5));
  uranus->setGasMass(EM(14.530 - 1.5));
  uranus->next_planet = neptune;
  
  saturn = new planet();
  saturn->setPlanetNo(7);
  saturn->setA(9.539);
  saturn->setE(0.056);
  saturn->setAxialTilt(26.7);
  saturn->setGasGiant(true);
  saturn->setDustMass(EM(9));
  saturn->setGasMass(EM(95.18 - 9));
  saturn->first_moon = tethys;
  saturn->next_planet = uranus;
  saturn->first_moon_backup = tethys;
  
  jupiter = new planet();
  jupiter->setPlanetNo(6);
  jupiter->setA(5.203);
  jupiter->setE(0.048);
  jupiter->setAxialTilt(3.1);
  jupiter->setGasGiant(true);
  jupiter->setDustMass(EM(10));
  jupiter->setGasMass(EM(317.9 - 10));
  jupiter->first_moon = io;
  jupiter->next_planet = saturn;
  jupiter->first_moon_backup = io;
  
  ceres = new planet();
  ceres->setPlanetNo(5);
  ceres->setA(2.766);
  ceres->setE(0.08);
  ceres->setGasGiant(false);
  ceres->setDustMass(EM(0.00015));
  ceres->next_planet = jupiter;
  
  mars = new planet();
  mars->setPlanetNo(4);
  mars->setA(1.524);
  mars->setE(0.093);
  mars->setAxialTilt(25.2);
  mars->setGasGiant(false);
  mars->setDustMass(EM(0.1074));
  mars->next_planet = ceres;
  
  earth = new planet();
  earth->setPlanetNo(3);
  earth->setA(1);
  earth->setE(0.017);
  earth->setAxialTilt(23.5);
  earth->setGasGiant(false);
  earth->setDustMass(EM(1.0));
  earth->first_moon = luna;
  earth->next_planet = mars;
  earth->first_moon_backup = luna;
  
  venus = new planet();
  venus->setPlanetNo(2);
  venus->setA(0.723);
  venus->setE(0.007);
  venus->setAxialTilt(177.3);
  venus->setGasGiant(false);
  venus->setDustMass(EM(0.815));
  venus->next_planet = earth;
  
  mercury = new planet();
  mercury->setPlanetNo(1);
  mercury->setA(0.387);
  mercury->setE(0.206);
  mercury->setAxialTilt(2);
  mercury->setGasGiant(false);
  mercury->setDustMass(EM(0.055));
  mercury->next_planet = venus;
  
  // exosolar planets
  eriEpsI = new planet();
  eriEpsI->setPlanetNo(1);
  eriEpsI->setA(3.3);
  eriEpsI->setE(0.608);
  eriEpsI->setGasGiant(true);
  eriEpsI->setDustMass(EM((1.55 * JUPITER_MASS) / 5.0));
  eriEpsI->setGasGiant(EM((1.55 * JUPITER_MASS) - ((1.55 * JUPITER_MASS) / 5.0)));
  
  UMa47III = new planet();
  UMa47III->setPlanetNo(3);
  UMa47III->setA(11.6);
  UMa47III->setE(0.16);
  UMa47III->setGasGiant(true);
  UMa47III->setDustMass(EM(1.64 * JUPITER_MASS) / 5.0);
  UMa47III->setGasMass(EM(1.64 * JUPITER_MASS) - (EM(1.64 * JUPITER_MASS) / 5.0));
  
  UMa47II = new planet();
  UMa47II->setPlanetNo(2);
  UMa47II->setA(3.73);
  UMa47II->setE(0.098);
  UMa47II->setGasGiant(true);
  UMa47II->setDustMass(EM(0.540 * JUPITER_MASS) / 5.0);
  UMa47II->setGasMass(EM(0.540 * JUPITER_MASS) - (EM(0.540 * JUPITER_MASS) / 5.0));
  UMa47II->next_planet = UMa47III;
  
  UMa47I = new planet();
  UMa47I->setPlanetNo(1);
  UMa47I->setA(2.11);
  UMa47I->setE(0.032);
  UMa47I->setGasGiant(true);
  UMa47I->setDustMass(EM(2.53 * JUPITER_MASS) / 5.0);
  UMa47I->setGasMass(EM(2.53 * JUPITER_MASS) - (EM(2.53 * JUPITER_MASS) / 5.0));
  UMa47I->next_planet = UMa47II;
  
  horIotI = new planet();
  horIotI->setPlanetNo(1);
  horIotI->setA(0.925);
  horIotI->setE(0.161);
  horIotI->setGasGiant(true);
  horIotI->setDustMass(EM(2.48 * JUPITER_MASS) / 5.0);
  horIotI->setGasMass(EM(2.48 * JUPITER_MASS) - (EM(2.48 * JUPITER_MASS) / 5.0));
  
  xiumaab = new planet();
  xiumaab->setPlanetNo(1);
  xiumaab->setA(0.8);
  xiumaab->setE(0.513);
  xiumaab->setGasGiant(true);
  xiumaab->setGasMass(0.4);
  
  xiumabb = new planet();
  xiumabb->setPlanetNo(1);
  xiumabb->setA(0.06);
  xiumabb->setGasGiant(true);
  xiumabb->setDustMass(EM(37.0 * JUPITER_MASS) / 5.0);
  xiumabb->setGasMass(EM(37.0 * JUPITER_MASS) - (EM(37.0 * JUPITER_MASS) / 5.0));
  
  Bellerophon = new planet();
  Bellerophon->setPlanetNo(1);
  Bellerophon->setA(0.0527);
  Bellerophon->setE(0.013);
  Bellerophon->setGasGiant(true);
  Bellerophon->setDustMass(EM(0.472 * JUPITER_MASS) / 5.0);
  Bellerophon->setGasMass(EM(0.472 * JUPITER_MASS) - (EM(0.472 * JUPITER_MASS) / 5.0));
  
  can55d = new planet();
  can55d->setPlanetNo(5);
  can55d->setA(5.76);
  can55d->setE(0.025);
  can55d->setGasGiant(true);
  can55d->setDustMass(EM(3.835 * JUPITER_MASS) / 5.0);
  can55d->setGasMass(EM(3.835 * JUPITER_MASS) - (EM(3.835 * JUPITER_MASS) / 5.0));
  
  can55f = new planet();
  can55f->setPlanetNo(4);
  can55f->setA(0.781);
  can55f->setE(0.0002);
  can55f->setGasGiant(true);
  can55f->setDustMass(EM(0.144 * JUPITER_MASS) / 5.0);
  can55f->setGasMass(EM(0.144 * JUPITER_MASS) - (EM(0.144 * JUPITER_MASS) / 5.0));
  can55f->next_planet = can55d;
  
  can55c = new planet();
  can55c->setPlanetNo(3);
  can55c->setA(0.2403);
  can55c->setE(0.053);
  can55c->setGasGiant(true);
  can55c->setDustMass(EM(0.169 * JUPITER_MASS) / 5.0);
  can55c->setGasMass(EM(0.169 * JUPITER_MASS) - (EM(0.169 * JUPITER_MASS) / 5.0));
  can55c->next_planet = can55f;
  
  can55b = new planet();
  can55b->setPlanetNo(2);
  can55b->setA(0.1134);
  can55b->setE(0.0159);
  can55b->setGasGiant(true);
  can55b->setDustMass(EM(0.8 * JUPITER_MASS) / 5.0);
  can55b->setGasMass(EM(0.8 * JUPITER_MASS)- (EM(0.8 * JUPITER_MASS) / 5.0));
  can55b->next_planet = can55c;
  
  can55e = new planet();
  can55e->setPlanetNo(1);
  can55e->setA(0.0156);
  can55e->setE(0.06);
  can55e->setGasGiant(false);
  can55e->setDustMass(EM(0.0261775162 * JUPITER_MASS));
  can55e->next_planet = can55b;
  
  UPSAndAe = new planet();
  UPSAndAe->setPlanetNo(4);
  UPSAndAe->setA(5.2456);
  UPSAndAe->setE(0.01);
  UPSAndAe->setDustMass(JUPITER_CORE_RATIO(336.7));
  UPSAndAe->setGasMass(JUPITER_GAS_RATIO(336.7));
  
  UPSAndAd = new planet();
  UPSAndAd->setPlanetNo(3);
  UPSAndAd->setA(2.55);
  UPSAndAd->setE(0.27);
  UPSAndAd->setDustMass(JUPITER_CORE_RATIO(3239.81));
  UPSAndAd->setGasMass(JUPITER_GAS_RATIO(3239.81));
  UPSAndAd->next_planet = UPSAndAe;
  
  UPSAndAc = new planet();
  UPSAndAc->setPlanetNo(2);
  UPSAndAc->setA(0.861);
  UPSAndAc->setE(0.24);
  UPSAndAc->setDustMass(JUPITER_CORE_RATIO(572.29));
  UPSAndAc->setGasMass(JUPITER_GAS_RATIO(572.29));
  UPSAndAc->next_planet = UPSAndAd;
  
  UPSAndAb = new planet();
  UPSAndAb->setPlanetNo(1);
  UPSAndAb->setA(0.059);
  UPSAndAb->setE(0.01);
  UPSAndAb->setDustMass(JUPITER_CORE_RATIO(197.12));
  UPSAndAb->setGasMass(JUPITER_GAS_RATIO(197.12));
  UPSAndAb->next_planet = UPSAndAc;
  
  hd10180h = new planet();
  hd10180h->setPlanetNo(9);
  hd10180h->setA(3.4);
  hd10180h->setE(0.08);
  hd10180h->setGasGiant(true);
  hd10180h->setDustMass(EM(65.8) / 5.0);
  hd10180h->setGasMass(EM(65.8) - (EM(65.8) / 5.0));
  
  hd10180g = new planet();
  hd10180g->setPlanetNo(8);
  hd10180g->setA(1.415);
  hd10180g->setE(0.03);
  hd10180g->setGasGiant(true);
  hd10180g->setDustMass(EM(21.4) / 5.0);
  hd10180g->setGasMass(EM(21.4) - (EM(21.4) / 5.0));
  hd10180g->next_planet = hd10180h;
  
  hd10180f = new planet();
  hd10180f->setPlanetNo(7);
  hd10180f->setA(0.4929);
  hd10180f->setE(0.13);
  hd10180f->setGasGiant(true);
  hd10180f->setDustMass(EM(23.9) / 5.0);
  hd10180f->setGasMass(EM(23.9) - (EM(23.9) / 5.0));
  hd10180f->next_planet = hd10180g;
  
  hd10180j = new planet();
  hd10180j->setPlanetNo(6);
  hd10180j->setA(0.33);
  hd10180j->setE(0.07);
  hd10180j->setGasGiant(true);
  hd10180j->setDustMass(EM(5.1) - (EM(5.1) / 10.0));
  hd10180j->setGasMass(EM(5.1) / 10.0);
  hd10180j->next_planet = hd10180f;
  
  hd10180e = new planet();
  hd10180e->setPlanetNo(5);
  hd10180e->setA(0.27);
  hd10180e->setE(0.001);
  hd10180e->setGasGiant(true);
  hd10180e->setDustMass(EM(25.0) / 5.0);
  hd10180e->setGasMass(EM(25.0) - (EM(25.0) / 5.0));
  hd10180e->next_planet = hd10180j;
  
  hd10180d = new planet();
  hd10180d->setPlanetNo(4);
  hd10180d->setA(0.1284);
  hd10180d->setE(0.011);
  hd10180d->setGasGiant(true);
  hd10180d->setDustMass(EM(11.9) / 5.0);
  hd10180d->setGasMass(EM(11.9) - (EM(11.9) / 5.0));
  hd10180d->next_planet = hd10180e;
  
  hd10180i = new planet();
  hd10180i->setPlanetNo(3);
  hd10180i->setA(0.0904);
  hd10180i->setE(0.05);
  hd10180i->setGasGiant(false);
  hd10180i->setDustMass(EM(1.9));
  hd10180i->next_planet = hd10180d;
  
  hd10180c = new planet();
  hd10180c->setPlanetNo(2);
  hd10180c->setA(0.0641);
  hd10180c->setE(0.07);
  hd10180c->setGasGiant(true);
  hd10180c->setDustMass(EM(13.0) / 5.0);
  hd10180c->setGasMass(EM(13.0) - (EM(13.0) / 5.0));
  hd10180c->next_planet = hd10180i;
  
  hd10180b = new planet();
  hd10180b->setA(0.02222);
  hd10180b->setE(0.0005);
  hd10180b->setGasGiant(false);
  hd10180b->setDustMass(EM(1.3));
  hd10180b->next_planet = hd10180c;
  
  gliese581f = new planet();
  gliese581f->setPlanetNo(6);
  gliese581f->setA(0.758);
  gliese581f->setGasGiant(false);
  gliese581f->setDustMass(EM(7.0));
  
  gliese581d = new planet();
  gliese581d->setPlanetNo(5);
  gliese581d->setA(0.21847);
  gliese581d->setGasGiant(false);
  gliese581d->setDustMass(EM(5.9));
  gliese581d->next_planet = gliese581f;
  
  gliese581g = new planet();
  gliese581g->setPlanetNo(4);
  gliese581g->setA(0.14601);
  gliese581g->setGasGiant(false);
  gliese581g->setDustMass(EM(2.24));
  gliese581g->next_planet = gliese581d;
  
  gliese581c = new planet();
  gliese581c->setPlanetNo(3);
  gliese581c->setA(0.072993);
  gliese581c->setGasGiant(false);
  gliese581c->setDustMass(EM(5.3));
  gliese581c->next_planet = gliese581g;
  
  gliese581b = new planet();
  gliese581b->setPlanetNo(2);
  gliese581b->setA(0.0406163);
  gliese581b->setGasGiant(true);
  gliese581b->setDustMass(EM(16.0) / 5.0);
  gliese581b->setGasMass(EM(16.0) - (EM(16.0) / 5.0));
  gliese581b->next_planet = gliese581c;
  
  gliese581e = new planet();
  gliese581e->setPlanetNo(1);
  gliese581e->setA(0.0284533);
  gliese581e->setGasGiant(false);
  gliese581e->setDustMass(EM(1.86));
  gliese581e->next_planet = gliese581b;
  
  hd10647b = new planet();
  hd10647b->setPlanetNo(1);
  hd10647b->setA(2.03);
  hd10647b->setE(0.16);
  hd10647b->setGasGiant(true);
  hd10647b->setDustMass(EM(0.93 * JUPITER_MASS) / 5.0);
  hd10647b->setGasMass(EM(0.93 * JUPITER_MASS) - (EM(0.93 * JUPITER_MASS) / 5.0));
  
  leo83Bb = new planet();
  leo83Bb->setPlanetNo(2);
  leo83Bb->setA(5.4);
  leo83Bb->setE(0.1);
  leo83Bb->setGasGiant(true);
  leo83Bb->setDustMass(EM(0.36 * JUPITER_MASS) / 5.0);
  leo83Bb->setGasMass(EM(0.36 * JUPITER_MASS) - (EM(0.36 * JUPITER_MASS) / 5.0));
  
  leo83Ba = new planet();
  leo83Ba->setPlanetNo(1);
  leo83Ba->setA(0.12186);
  leo83Ba->setE(0.13);
  leo83Ba->setGasGiant(true);
  leo83Ba->setDustMass(EM(0.087 * JUPITER_MASS) / 5.0);
  leo83Ba->setGasMass(EM(0.087 * JUPITER_MASS) - (EM(0.087 * JUPITER_MASS) / 5.0));
  leo83Ba->next_planet = leo83Bb;
  
  muarie = new planet();
  muarie->setPlanetNo(4);
  muarie->setA(5.235);
  muarie->setE(0.0985);
  muarie->setGasGiant(true);
  muarie->setDustMass(EM(1.814 * JUPITER_MASS) / 5.0);
  muarie->setGasMass(EM(1.814 * JUPITER_MASS) - (EM(1.814 * JUPITER_MASS) / 5.0));
  
  muarib = new planet();
  muarib->setPlanetNo(3);
  muarib->setA(1.497);
  muarib->setE(0.128);
  muarib->setGasGiant(true);
  muarib->setDustMass(EM(1.676 * JUPITER_MASS) / 5.0);
  muarib->setGasMass(EM(1.676 * JUPITER_MASS) - (EM(1.676 * JUPITER_MASS) / 5.0));
  muarib->next_planet = muarie;
  
  muarid = new planet();
  muarid->setPlanetNo(2);
  muarid->setA(0.921);
  muarid->setE(0.0666);
  muarid->setGasGiant(true);
  muarid->setDustMass(EM(0.5219 * JUPITER_MASS) / 5.0);
  muarid->setGasMass(EM(0.5219 * JUPITER_MASS) - (EM(0.5219 * JUPITER_MASS) / 5.0));
  muarid->next_planet = muarib;
  
  muaric = new planet();
  muaric->setPlanetNo(1);
  muaric->setA(0.09094);
  muaric->setE(0.172);
  muaric->setGasGiant(true);
  muaric->setDustMass(EM(0.03321 * JUPITER_MASS) - (EM(0.03321 * JUPITER_MASS) / 10.0));
  muaric->setGasMass(EM(0.03321 * JUPITER_MASS) / 10.0);
  muaric->next_planet = muarid;
  
  hd28185b = new planet();
  hd28185b->setPlanetNo(1);
  hd28185b->setA(1.03);
  hd28185b->setE(0.07);
  hd28185b->setGasGiant(true);
  hd28185b->setDustMass(JUPITER_CORE_RATIO(1812.26));
  hd28185b->setGasMass(JUPITER_GAS_RATIO(1812.26));
  
  hd40307g = new planet();
  hd40307g->setPlanetNo(6);
  hd40307g->setA(0.6);
  hd40307g->setE(0.29);
  hd40307g->setGasGiant(false);
  hd40307g->setDustMass(EM(7.09));
  
  hd40307f = new planet();
  hd40307f->setPlanetNo(5);
  hd40307f->setA(0.247);
  hd40307f->setE(0.02);
  hd40307f->setGasGiant(false);
  hd40307f->setDustMass(EM(5.21));
  hd40307f->next_planet = hd40307g;
  
  hd40307e = new planet();
  hd40307e->setPlanetNo(4);
  hd40307e->setA(0.1886);
  hd40307e->setE(0.15);
  hd40307e->setGasGiant(false);
  hd40307e->setDustMass(EM(3.5));
  hd40307e->next_planet = hd40307f;
  
  hd40307d = new planet();
  hd40307d->setPlanetNo(3);
  hd40307d->setA(0.1321);
  hd40307d->setE(0.07);
  hd40307d->setGasGiant(false);
  hd40307d->setDustMass(EM(9.51));
  hd40307d->next_planet = hd40307e;
  
  hd40307c = new planet();
  hd40307c->setPlanetNo(2);
  hd40307c->setA(0.0799);
  hd40307c->setE(0.06);
  hd40307c->setGasGiant(false);
  hd40307c->setDustMass(EM(6.61));
  hd40307c->next_planet = hd40307d;
  
  hd40307b = new planet();
  hd40307b->setPlanetNo(1);
  hd40307b->setA(0.0468);
  hd40307b->setE(0.2);
  hd40307b->setGasGiant(false);
  hd40307b->setDustMass(EM(4.01));
  hd40307b->next_planet = hd40307c;
  
  kepler22b = new planet();
  kepler22b->setPlanetNo(1);
  kepler22b->setA(0.849);
  kepler22b->setGasGiant(false);
  kepler22b->setDustMass(EM(20.36));
  
  taucetf = new planet();
  taucetf->setPlanetNo(5);
  taucetf->setA(1.35);
  taucetf->setE(0.03);
  taucetf->setGasGiant(false);
  taucetf->setDustMass(EM(6.67));
  
  taucete = new planet();
  taucete->setPlanetNo(4);
  taucete->setA(0.552);
  taucete->setE(0.05);
  taucete->setGasGiant(false);
  taucete->setDustMass(EM(4.29));
  taucete->next_planet = taucetf;
  
  taucetd = new planet();
  taucetd->setPlanetNo(3);
  taucetd->setA(0.374);
  taucetd->setE(0.08);
  taucetd->setGasGiant(false);
  taucetd->setDustMass(EM(3.5));
  taucetd->next_planet = taucete;
  
  taucetc = new planet();
  taucetc->setPlanetNo(2);
  taucetc->setA(0.195);
  taucetc->setE(0.03);
  taucetc->setGasGiant(false);
  taucetc->setDustMass(EM(3.11));
  taucetc->next_planet = taucetd;
  
  taucetb = new planet();
  taucetb->setPlanetNo(1);
  taucetb->setA(0.105);
  taucetb->setE(0.16);
  taucetb->setGasGiant(false);
  taucetb->setDustMass(EM(2.0));
  taucetb->next_planet = taucetc;
  
  alfcentbb = new planet();
  alfcentbb->setPlanetNo(1);
  alfcentbb->setA(0.04);
  alfcentbb->setGasGiant(false);
  alfcentbb->setDustMass(EM(0.934));
  alfcentbb->next_planet = NULL;
  
  EPSEric = new planet();
  EPSEric->setPlanetNo(2);
  EPSEric->setA(40);
  EPSEric->setE(0.3);
  EPSEric->setGasGiant(true);
  EPSEric->setDustMass(EM(30.0) / 5.0);
  EPSEric->setGasMass(EM(30.0) - (EM(30.0) / 5.0));
  
  EPSErib = new planet();
  EPSErib->setPlanetNo(1);
  EPSErib->setA(3.39);
  EPSErib->setE(0.702);
  EPSErib->setGasGiant(true);
  EPSErib->setDustMass(EM(490.0) / 5.0);
  EPSErib->setGasMass(EM(490.0) - (EM(490.0) / 5.0));
  EPSErib->next_planet = EPSEric;
  
  cyteen = new planet();
  cyteen->setPlanetNo(1);
  cyteen->setA(0.098);
  cyteen->setE(0.01);
  cyteen->setAxialTilt(18.5);
  cyteen->setGasGiant(false);
  cyteen->setDustMass(EM(0.7));
  
  GL849b = new planet();
  GL849b->setPlanetNo(1);
  GL849b->setA(2.35);
  GL849b->setE(0.07);
  GL849b->setGasGiant(true);
  GL849b->setDustMass(EM(260.0) / 5.0);
  GL849b->setGasMass(EM(260.0) - (EM(260.0) / 5.0));
  
  ILAqrb = new planet();
  ILAqrb->setPlanetNo(3);
  ILAqrb->setA(0.208317);
  ILAqrb->setE(0.0324);
  ILAqrb->setGasGiant(true);
  ILAqrb->setDustMass(EM(720.0) / 5.0);
  ILAqrb->setGasMass(EM(720.0) - (EM(720.0) / 5.0));
  
  ILAqrc = new planet();
  ILAqrc->setPlanetNo(2);
  ILAqrc->setA(0.12959);
  ILAqrc->setE(0.25591);
  ILAqrc->setGasGiant(true);
  ILAqrc->setDustMass(EM(230.0) / 5.0);
  ILAqrc->setGasMass(EM(230.0) - (EM(230.0) / 5.0));
  ILAqrc->next_planet = ILAqrb;
  
  ILAqrd = new planet();
  ILAqrd->setPlanetNo(1);
  ILAqrd->setA(0.020807);
  ILAqrd->setE(0.207);
  ILAqrd->setGasGiant(false);
  ILAqrd->setDustMass(EM(7.0));
  ILAqrd->next_planet = ILAqrc;
  
  HD20794d = new planet();
  HD20794d->setPlanetNo(3);
  HD20794d->setA(0.3499);
  HD20794d->setGasGiant(false);
  HD20794d->setDustMass(EM(5.0));
  
  HD20794c = new planet();
  HD20794c->setPlanetNo(2);
  HD20794c->setA(0.2036);
  HD20794c->setGasGiant(false);
  HD20794c->setDustMass(EM(2.0));
  HD20794c->next_planet = HD20794d;
  
  HD20794b = new planet();
  HD20794b->setPlanetNo(1);
  HD20794b->setA(0.1207);
  HD20794b->setGasGiant(false);
  HD20794b->setDustMass(EM(3.0));
  HD20794b->next_planet = HD20794c;
  
  BETHyib = new planet();
  BETHyib->setPlanetNo(1);
  BETHyib->setA(8);
  BETHyib->setGasGiant(true);
  BETHyib->setDustMass(EM(1100.0) / 5.0);
  BETHyib->setGasMass(EM(1100.0) - (EM(1100.0) / 5.0));
  
  hd208527b = new planet();
  hd208527b->setPlanetNo(1);
  hd208527b->setA(2.1);
  hd208527b->setE(0.08);
  hd208527b->setGasGiant(true);
  hd208527b->setDustMass(EM(9.9 * JUPITER_MASS) / 5.0);
  hd208527b->setGasMass(EM(9.9 * JUPITER_MASS) - (EM(9.9 * JUPITER_MASS) / 5.0));
  
  kepler11g = new planet();
  kepler11g->setPlanetNo(6);
  kepler11g->setA(0.462);
  kepler11g->setDustMass(EM(6.03));
  kepler11g->setGasMass(EM(6.03));
  
  kepler11f = new planet();
  kepler11f->setPlanetNo(5);
  kepler11f->setA(0.25);
  kepler11f->setDustMass(EM(2.0) * (1.0 - (4.0 / 100.0)));
  kepler11f->setGasMass(EM(2.0) * (4.0 / 100.0));
  kepler11f->next_planet = kepler11g;
  
  kepler11e = new planet();
  kepler11e->setPlanetNo(4);
  kepler11e->setA(0.194);
  kepler11e->setDustMass(EM(8.0) * (1.0 - (15.7 / 100.0)));
  kepler11e->setGasMass(EM(8.0) * (15.7 / 100.0));
  kepler11e->next_planet = kepler11f;
  
  kepler11d = new planet();
  kepler11d->setA(0.159);
  kepler11d->setDustMass(EM(7.3) * (1.0 - (6.6 / 100.0)));
  kepler11d->setGasMass(EM(7.3) * (6.6 / 100.0));
  kepler11d->next_planet = kepler11e;
  
  kepler11c = new planet();
  kepler11c->setA(0.106);
  kepler11c->setDustMass(EM(2.9) * (1.0 - (5.0 / 100.0)));
  kepler11c->setGasMass(EM(2.9) * (5.0 / 100.0));
  kepler11c->next_planet = kepler11d;
  
  kepler11b = new planet();
  kepler11b->setA(0.091);
  kepler11b->setDustMass(EM(1.9) * (1.0 - (0.51 / 100.0)));
  kepler11b->setGasMass(EM(1.9) * (0.51 / 100.0));
  kepler11b->next_planet = kepler11c;
  
  bajorXIV = new planet();
  bajorXIV->setA(19.562261134889);
  bajorXIV->setE(0.022156249102282);
  bajorXIV->setDustMass(EM(0.5228151039924793));
  
  bajorXIII = new planet();
  bajorXIII->setA(17.204317230677);
  bajorXIII->setE(0.049231073388664);
  bajorXIII->setDustMass(EM(0.7020456615006141));
  bajorXIII->next_planet = bajorXIV;
  
  bajorXII = new planet();
  bajorXII->setA(14.671698311495);
  bajorXII->setE(0.033240633250561);
  bajorXII->setDustMass(EM(0.2628715778036144));
  bajorXII->next_planet = bajorXIII;
  
  bajorXI = new planet();
  bajorXI->setA(11.739328956375);
  bajorXI->setE(0.032305684586002);
  bajorXI->setDustMass(EM(41.574513206976015));
  bajorXI->setGasMass(EM(173.4278864659173));
  bajorXI->next_planet = bajorXII;
  
  bajorX = new planet();
  bajorX->setA(6.8609384900303);
  bajorX->setE(0.02730538824569);
  bajorX->setDustMass(EM(98.41815904981001));
  bajorX->setGasMass(EM(2055.5513560810678));
  bajorX->next_planet = bajorXI;
  
  bajorIX = new planet();
  bajorIX->setA(3.9163295068046);
  bajorIX->setE(0.024780349949406);
  bajorIX->setDustMass(EM(47.56970388323728));
  bajorIX->setGasMass(EM(1244.3898973267437));
  bajorIX->next_planet = bajorX;
  
  bajorVIII2 = new planet();
  bajorVIII2->setDustMass(EM(0.01248163264128256));
  bajorVIII2->setDeletable(false);
  bajorVIII2->reconnect_to = NULL;
  
  bajorVIII1 = new planet();
  bajorVIII1->setDustMass(EM(0.0559390238548234902890198034));
  bajorVIII1->next_planet = bajorVIII2;
  bajorVIII1->setDeletable(false);
  bajorVIII1->reconnect_to = bajorVIII2;
  
  bajorVIII = new planet();
  bajorVIII->setA(1.2928937846493);
  bajorVIII->setE(0.010224984980454);
  bajorVIII->setDustMass(EM(1.3080413057739237));
  bajorVIII->first_moon = bajorVIII1;
  bajorVIII->next_planet = bajorIX;
  bajorVIII->first_moon_backup = bajorVIII1;
  
  bajorVII3 = new planet();
  bajorVII3->setDustMass(EM(0.000000290721478925789234789234789));
  bajorVII3->setDeletable(false);
  bajorVII3->reconnect_to = NULL;
  
  bajorVII2 = new planet();
  bajorVII2->setDustMass(EM(0.0000031388457878548902389049034820));
  bajorVII2->next_planet = bajorVII3;
  bajorVII2->setDeletable(false);
  bajorVII2->reconnect_to = bajorVII3;
  
  bajorVII1 = new planet();
  bajorVII1->setDustMass(EM(0.0050193477890590348903590234));
  bajorVII1->next_planet = bajorVII2;
  bajorVII1->setDeletable(false);
  bajorVII1->reconnect_to = bajorVII2;
  
  derna = new planet();
  derna->setDustMass(EM(0.0103490578758902348490));
  derna->next_planet = bajorVII1;
  derna->setDeletable(false);
  derna->reconnect_to = bajorVII1;
  
  jeraddo = new planet();
  jeraddo->setDustMass(2.6991354182205E-6);
  jeraddo->next_planet = derna;
  jeraddo->setDeletable(false);
  jeraddo->reconnect_to = derna;
  
  bajorVII = new planet();
  bajorVII->setA(1.0617776415431);
  bajorVII->setE(0.010056496949484);
  bajorVII->setDustMass(EM(1.20067295628399508476));
  bajorVII->first_moon = jeraddo;
  bajorVII->next_planet = bajorVIII;
  bajorVII->first_moon_backup = jeraddo;
 
  bajorVI = new planet();
  bajorVI->setA(0.80688692980298);
  bajorVI->setE(0.0023862583761025);
  bajorVI->setDustMass(EM(1.4276468931113457));
  bajorVI->next_planet = bajorVII;
  
  bajorV = new planet();
  bajorV->setA(0.66261211809021);
  bajorV->setE(0.0040807227436307);
  bajorV->setDustMass(EM(1.072391437827747));
  bajorV->next_planet = bajorVI;

  bajorIV = new planet();
  bajorIV->setA(0.49860599934078);
  bajorIV->setE(0.014039390637021);
  bajorIV->setDustMass(EM(0.04038226969212624));
  bajorIV->next_planet = bajorV;
  
  bajorIII = new planet();
  bajorIII->setA(0.37223529220779);
  bajorIII->setE(0.0048019249254612);
  bajorIII->setDustMass(EM(0.019201363541128676));
  bajorIII->next_planet = bajorIV;
  
  bajorII = new planet();
  bajorII->setA(0.25364871562867);
  bajorII->setE(0.10440638879792);
  bajorII->setDustMass(EM(0.042657657162862156));
  bajorII->next_planet = bajorIII;
 
  bajorI = new planet();
  bajorI->setA(0.13697339487414);
  bajorI->setE(0.10492514490814);
  bajorI->setDustMass(EM(0.0347719346132302));
  bajorI->next_planet = bajorII;
  
  gliese667Cg = new planet();
  gliese667Cg->setA(0.5389);
  gliese667Cg->setE(0.08);
  gliese667Cg->setDustMass(EM(4.6));
  
  gliese667Cd = new planet();
  gliese667Cd->setA(0.2758);
  gliese667Cd->setE(0.03);
  gliese667Cd->setDustMass(EM(5.1));
  gliese667Cd->next_planet = gliese667Cg;
  
  gliese667Ce = new planet();
  gliese667Ce->setA(0.21257);
  gliese667Ce->setE(0.02);
  gliese667Ce->setDustMass(EM(2.7));
  gliese667Ce->next_planet = gliese667Cd;
  
  gliese667Cf = new planet();
  gliese667Cf->setA(0.15575);
  gliese667Cf->setE(0.03);
  gliese667Cf->setDustMass(EM(2.7));
  gliese667Cf->next_planet = gliese667Ce;
  
  gliese667Cc = new planet();
  gliese667Cc->setA(0.12507);
  gliese667Cc->setE(0.02);
  gliese667Cc->setDustMass(EM(3.8));
  gliese667Cc->next_planet = gliese667Cf;
  
  gliese667Ch = new planet();
  gliese667Ch->setA(0.085);
  gliese667Ch->setE(0.06);
  gliese667Ch->setDustMass(EM(1.1));
  gliese667Ch->next_planet = gliese667Cc;
  
  gliese667Cb = new planet();
  gliese667Cb->setA(0.050432);
  gliese667Cb->setE(0.113);
  gliese667Cb->setDustMass(EM(5.6));
  gliese667Cb->next_planet = gliese667Ch;
  
  kepler283c = new planet();
  kepler283c->setA(0.341);
  kepler283c->setDustMass(EM(7.04));
  
  kepler283b = new planet();
  kepler283b->setA(0.0815);
  kepler283b->setDustMass(EM(13.26));
  kepler283b->next_planet = kepler283c;
  
  kepler62f = new planet();
  kepler62f->setA(0.718);
  kepler62f->setDustMass(EM(2.81));
  
  kepler62e = new planet();
  kepler62e->setA(0.427);
  kepler62e->setDustMass(EM(4.54));
  kepler62e->next_planet = kepler62f;
  
  kepler62d = new planet();
  kepler62d->setA(0.12);
  kepler62d->setDustMass(EM(9.29));
  kepler62d->next_planet = kepler62e;
  
  kepler62c = new planet();
  kepler62c->setA(0.0929);
  kepler62c->setDustMass(EM(0.12));
  kepler62c->next_planet = kepler62d;
  
  kepler62b = new planet();
  kepler62b->setA(0.0553);
  kepler62b->setDustMass(EM(2.17));
  kepler62b->next_planet = kepler62c;
  
  kepler296f = new planet();
  kepler296f->setA(0.263);
  kepler296f->setDustMass(EM(6.72));
  
  kepler296e = new planet();
  kepler296e->setA(0.174);
  kepler296e->setDustMass(EM(6.1));
  kepler296e->next_planet = kepler296f;
  
  kepler296d = new planet();
  kepler296d->setA(0.122);
  kepler296d->setDustMass(EM(17.55));
  kepler296d->next_planet = kepler296e;
  
  kepler296c = new planet();
  kepler296c->setA(0.054);
  kepler296c->setDustMass(EM(13.85));
  kepler296c->next_planet = kepler296d;
  
  kepler296b = new planet();
  kepler296b->setA(0.039);
  kepler296b->setDustMass(EM(0.71));
  kepler296b->next_planet = kepler296c;
  
  gliese180c = new planet();
  gliese180c->setA(0.129);
  gliese180c->setE(0.09);
  gliese180c->setDustMass(EM(6.4));
  
  gliese180b = new planet();
  gliese180b->setA(0.103);
  gliese180b->setE(0.11);
  gliese180b->setDustMass(EM(8.3));
  gliese180b->next_planet = gliese180c;
  
  gliese163d = new planet();
  gliese163d->setA(1.0269);
  gliese163d->setE(0.4);
  gliese163d->setDustMass(EM(22.08 / 2.0));
  gliese163d->setGasMass(EM(22.08 / 2.0));
  
  gliese163c = new planet();
  gliese163c->setA(0.1254);
  gliese163c->setE(0.09);
  gliese163c->setDustMass(EM(7.26));
  gliese163c->next_planet = gliese163d;
  
  gliese163b = new planet();
  gliese163b->setA(0.0607);
  gliese163b->setE(0.01);
  gliese163b->setDustMass(EM(10.62 / 2.0));
  gliese163b->setGasMass(EM(10.62 / 2.0));
  gliese163b->next_planet = gliese163c;
  
  kepler61b = new planet();
  kepler61b->setA(0.27);
  kepler61b->setE(0.25);
  kepler61b->setDustMass(EM(13.85));
  
  gliese422b = new planet();
  gliese422b->setA(0.119);
  gliese422b->setE(0.05);
  gliese422b->setDustMass(EM(9.9));
  
  kepler298d = new planet();
  kepler298d->setA(0.305);
  kepler298d->setDustMass(EM(26.81));
  
  kepler298c = new planet();
  kepler298c->setA(0.136);
  kepler298c->setDustMass(EM(8.88));
  kepler298c->next_planet = kepler298d;
  
  kepler298b = new planet();
  kepler298b->setA(0.08);
  kepler298b->setDustMass(EM(9.51));
  kepler298b->next_planet = kepler298c;
  
  kepler174d = new planet();
  kepler174d->setA(0.68);
  kepler174d->setDustMass(EM(14.78));
  
  kepler174c = new planet();
  kepler174c->setA(0.214);
  kepler174c->setDustMass(EM(3.4));
  kepler174c->next_planet = kepler174d;
  
  kepler174b = new planet();
  kepler174b->setA(0.1);
  kepler174b->setDustMass(EM(9.51));
  kepler174b->next_planet = kepler174c;
  
  gliese682c = new planet();
  gliese682c->setA(0.176);
  gliese682c->setE(0.1);
  gliese682c->setDustMass(EM(8.7));
  
  gliese682b = new planet();
  gliese682b->setA(0.08);
  gliese682b->setE(0.08);
  gliese682b->setDustMass(EM(4.4));
  gliese682b->next_planet = gliese682c;
  
  hd38529c = new planet();
  hd38529c->setA(3.695);
  hd38529c->setE(0.36);
  hd38529c->setDustMass(JUPITER_CORE_RATIO(5627.54));
  hd38529c->setGasMass(JUPITER_GAS_RATIO(5627.54));
  
  hd38529b = new planet();
  hd38529b->setA(0.131);
  hd38529b->setE(0.25);
  hd38529b->setDustMass(JUPITER_CORE_RATIO(247.99));
  hd38529b->setGasMass(JUPITER_GAS_RATIO(247.99));
  hd38529b->next_planet = hd38529c;
  
  hd202206c = new planet();
  hd202206c->setA(2.55);
  hd202206c->setE(0.27);
  hd202206c->setDustMass(JUPITER_CORE_RATIO(775.77));
  hd202206c->setGasMass(JUPITER_GAS_RATIO(775.77));
  
  hd202206b = new planet();
  hd202206b->setA(0.83);
  hd202206b->setE(0.43);
  hd202206b->setDustMass(JUPITER_CORE_RATIO(5532.16));
  hd202206b->setGasMass(JUPITER_GAS_RATIO(5532.16));
  hd202206b->next_planet = hd202206c;
  
  hd8673b = new planet();
  hd8673b->setA(3.02);
  hd8673b->setE(0.72);
  hd8673b->setDustMass(JUPITER_CORE_RATIO(4514.75));
  hd8673b->setGasMass(JUPITER_GAS_RATIO(4514.75));
  
  hd22781b = new planet();
  hd22781b->setA(1.167);
  hd22781b->setE(0.82);
  hd22781b->setDustMass(JUPITER_CORE_RATIO(4339.88));
  hd22781b->setGasMass(JUPITER_GAS_RATIO(4339.88));
  
  hd217786b = new planet();
  hd217786b->setA(2.38);
  hd217786b->setE(0.4);
  hd217786b->setDustMass(JUPITER_CORE_RATIO(4133.22));
  hd217786b->setGasMass(JUPITER_GAS_RATIO(4133.22));
  
  hd106270b = new planet();
  hd106270b->setA(4.3);
  hd106270b->setE(0.4);
  hd106270b->setDustMass(JUPITER_CORE_RATIO(3497.34));
  hd106270b->setGasMass(JUPITER_GAS_RATIO(3497.34));
  
  hd38801b = new planet();
  hd38801b->setA(1.7);
  hd38801b->setDustMass(JUPITER_CORE_RATIO(3401.96));
  hd38801b->setGasMass(JUPITER_GAS_RATIO(3401.96));
  
  hd39091b = new planet();
  hd39091b->setA(3.28);
  hd39091b->setE(0.61);
  hd39091b->setDustMass(JUPITER_CORE_RATIO(3274.78));
  hd39091b->setGasMass(JUPITER_GAS_RATIO(3274.78));
  
  hd141937b = new planet();
  hd141937b->setA(1.52);
  hd141937b->setE(0.41);
  hd141937b->setDustMass(JUPITER_CORE_RATIO(3084.02));
  hd141937b->setGasMass(JUPITER_GAS_RATIO(3084.02));
  
  hd33564b = new planet();
  hd33564b->setA(1.1);
  hd33564b->setE(0.34);
  hd33564b->setDustMass(JUPITER_CORE_RATIO(2893.25));
  hd33564b->setGasMass(JUPITER_GAS_RATIO(2893.25));
  
  hd23596b = new planet();
  hd23596b->setA(2.88);
  hd23596b->setE(0.29);
  hd23596b->setDustMass(JUPITER_CORE_RATIO(2575.31));
  hd23596b->setGasMass(JUPITER_GAS_RATIO(2575.31));
  
  hd222582b = new planet();
  hd222582b->setA(1.35);
  hd222582b->setE(0.72);
  hd222582b->setDustMass(JUPITER_CORE_RATIO(2464.04));
  hd222582b->setGasMass(JUPITER_GAS_RATIO(2464.04));
  
  hd86264b = new planet();
  hd86264b->setA(2.86);
  hd86264b->setE(0.7);
  hd86264b->setDustMass(JUPITER_CORE_RATIO(2225.58));
  hd86264b->setGasMass(JUPITER_GAS_RATIO(2225.58));
  
  hd196067b = new planet();
  hd196067b->setA(5.02);
  hd196067b->setE(0.66);
  hd196067b->setDustMass(JUPITER_CORE_RATIO(2193.79));
  hd196067b->setGasMass(JUPITER_GAS_RATIO(2193.79));
  
  hd10697b = new planet();
  hd10697b->setA(2.16);
  hd10697b->setE(0.1);
  hd10697b->setDustMass(JUPITER_CORE_RATIO(2028.46));
  hd10697b->setGasMass(JUPITER_GAS_RATIO(2028.46));
  
  hd132406b = new planet();
  hd132406b->setA(1.98);
  hd132406b->setE(0.34);
  hd132406b->setDustMass(JUPITER_CORE_RATIO(1783.64));
  hd132406b->setGasMass(JUPITER_GAS_RATIO(1783.64));
  
  hd13908c = new planet();
  hd13908c->setA(2.03);
  hd13908c->setE(0.12);
  hd13908c->setDustMass(JUPITER_CORE_RATIO(1631.03));
  hd13908c->setGasMass(JUPITER_GAS_RATIO(1631.03));
  
  hd13908b = new planet();
  hd13908b->setA(0.154);
  hd13908b->setE(0.05);
  hd13908b->setDustMass(JUPITER_CORE_RATIO(275.02));
  hd13908b->setGasMass(JUPITER_GAS_RATIO(275.02));
  hd13908b->next_planet = hd13908c;
  
  hd2039b = new planet();
  hd2039b->setA(2.2);
  hd2039b->setE(0.67);
  hd2039b->setDustMass(JUPITER_CORE_RATIO(1557.91));
  hd2039b->setGasMass(JUPITER_GAS_RATIO(1557.91));
  
  hd82943d = new planet();
  hd82943d->setA(2.145);
  hd82943d->setDustMass(JUPITER_CORE_RATIO(92.2));
  hd82943d->setGasMass(JUPITER_GAS_RATIO(92.2));
  
  hd82943b = new planet();
  hd82943b->setA(1.19);
  hd82943b->setE(0.2);
  hd82943b->setDustMass(JUPITER_CORE_RATIO(1526.11));
  hd82943b->setGasMass(JUPITER_GAS_RATIO(1526.11));
  hd82943b->next_planet = hd82943d;
  
  hd82943c = new planet();
  hd82943c->setA(0.746);
  hd82943c->setE(0.42);
  hd82943c->setDustMass(JUPITER_CORE_RATIO(1519.75));
  hd82943c->setGasMass(JUPITER_GAS_RATIO(1519.75));
  hd82943c->next_planet = hd82943b;
  
  moa2011blg293lb = new planet();
  moa2011blg293lb->setA(1.1);
  moa2011blg293lb->setDustMass(JUPITER_CORE_RATIO(1526.11));
  moa2011blg293lb->setGasMass(JUPITER_GAS_RATIO(1526.11));
  
  hd213240b = new planet();
  hd213240b->setA(2.03);
  hd213240b->setE(0.45);
  hd213240b->setDustMass(JUPITER_CORE_RATIO(1430.73));
  hd213240b->setGasMass(JUPITER_GAS_RATIO(1430.73));
  
  kepler186f = new planet();
  kepler186f->setA(0.3926);
  kepler186f->setKnownRadius(1.13);
  
  kepler186e = new planet();
  kepler186e->setA(0.1216);
  kepler186e->setKnownRadius(1.33);
  kepler186e->next_planet = kepler186f;
  
  kepler186d = new planet();
  kepler186d->setA(0.0861);
  kepler186d->setKnownRadius(1.39);
  kepler186d->next_planet = kepler186e;
  
  kepler186c = new planet();
  kepler186c->setA(0.0574);
  kepler186c->setKnownRadius(1.25);
  kepler186c->next_planet = kepler186d;
  
  kepler186b = new planet();
  kepler186b->setA(0.0378);
  kepler186b->setKnownRadius(1.08);
  kepler186b->next_planet = kepler186c;
  
  kapteync = new planet();
  kapteync->setA(0.311);
  kapteync->setE(0.23);
  kepler11c->setDustMass(EM(7.0));
  
  kapteynb = new planet();
  kapteynb->setA(0.168);
  kapteynb->setE(0.21);
  kapteynb->setDustMass(EM(4.7));
  kapteynb->next_planet = kapteync;
}