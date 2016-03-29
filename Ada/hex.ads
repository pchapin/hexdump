---------------------------------------------------------------------------
-- FILE          : hex.ads
-- LAST REVISION : 2006-07-05
-- SUBJECT       : Specification of a package for manipulating hex strings.
-- PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin
--
-- Please send comments or bug reports to
--
--      Peter C. Chapin
--      Electrical and Computer Engineering Technology
--      Vermont Technical College
--      Randolph Center, VT 05061
--      pchapin@ecet.vtc.edu
---------------------------------------------------------------------------

with Interfaces;

package Hex is
   -- Convert an 8 bit quantity to a two digit hex string.
   function To_String(Value : Interfaces.Unsigned_8) return String;

   -- Convert a 32 bit quantity to a four digit hex string.
   function To_String(Value : Interfaces.Unsigned_32) return String;
end Hex;
