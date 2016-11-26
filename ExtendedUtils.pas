unit ExtendedUtils;

interface

function GetScPref(v: Extended; n: Byte; meas: UnicodeString): UnicodeString;
function GetCompPref(v: Int64; n: Byte): UnicodeString;

implementation

uses
  Math, SysUtils;

function GetScPref(v: Extended; n: Byte; meas: UnicodeString): UnicodeString;
var
  t: integer;
const
  pref: array [-8 .. 8] of UnicodeString = ('Ë', 'Á', '‡', 'Ù', 'Ô', 'Ì', 'ÏÍ', 'Ï', '', 'Í', 'Ã', '√', '“', 'œ', '›',
    '«', '»');
begin
  if InRange(v, -10, 10) then
    Exit(FloatToStr(RoundTo(v, -n)) + ' ' + pref[0] + meas);
  t := EnsureRange(trunc(logN(990, abs(v))) + (sign(ln(abs(v))) - 1) div 2, -8, 8);
  Result := FloatToStr(RoundTo(v * power(10, -min(max(t * 3, -24), 24)), -n)) + ' ' + pref[t] + meas;
end;

function GetCompPref(v: Int64; n: Byte): UnicodeString;
var
  t: integer;
const
  pref: array [0 .. 8] of UnicodeString = ('', ' Ë', 'ÃË', '√Ë', '“Ë', 'œË', '›Ë', '«Ë', '…Ë');
begin
  if InRange(v, 0, 10) then
    Exit(FloatToStr(RoundTo(v, -n)) + ' ' + pref[0] + '¡');
  t := EnsureRange(trunc(logN(990, abs(v))), 0, 8);
  Result := FloatToStr(RoundTo(v * power(2, -min(t * 10, 80)), -n)) + ' ' + pref[t] + '¡';
end;

end.
