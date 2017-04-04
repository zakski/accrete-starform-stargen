(*----------------------------------------------------------------------*)
(* Copywrite (C) 1988 Matthew Burdick					*)
(* This code may be freely distributed.					*)
(*----------------------------------------------------------------------*)
   Function Power (variable, exponent : real) : real;
      Begin
         if (variable <= 0.0)
            then power:= 0.0
            else power:= Exp(exponent * ln(variable));
      End;

   Function Random_number (inner, outer : real) : real;
(*----------------------------------------------------------------------*)
(*  This function returns a random real number between the specified    *)
(* inner and outer bounds.                                              *)
(*----------------------------------------------------------------------*)
      VAR  range : real;
      Begin
         Range:= outer - inner;
         Random_number:= random*range + inner;
      End;

   Function about (value, variation : real) : real;
(*----------------------------------------------------------------------*)
(*   This function returns a value within a certain variation of the    *)
(*   exact value given it in 'value'.                                   *)
(*----------------------------------------------------------------------*)
   Begin
      about:= value + (value * random_number(-variation, variation));
   End;

   Function Random_eccentricity : real;
      Begin
         Random_eccentricity:= 1.0 - power(random, eccentricity_coeff);
      End;

