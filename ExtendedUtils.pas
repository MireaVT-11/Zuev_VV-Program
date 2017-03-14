unit ExtendedUtils;

interface

function GetScPref(v: Extended; n: Byte; meas: UnicodeString): UnicodeString;
function GetCompPref(v: Int64; n: Byte): UnicodeString;

implementation

uses
  System.Math, System.SysUtils;

function GetScPref(v: Extended; n: Byte; meas: UnicodeString): UnicodeString;
var
  t: integer;
const
  //Содержит кратные приставки СИ в Юникоде
  pref: array [-8 .. 8] of UnicodeString = (#$0438, #$0437, #$0430, #$0444, #$043F, #$043D, #$043C#$043A, #$043C , '', #$043A, #$041C, #$0413, #$0422, #$041F, #$042D, #$0417, #$0418);
begin
  if IsZero(v) then
    Exit('0 ' + pref[0] + meas);
  t := EnsureRange(trunc(logN(990, abs(v))) + (sign(ln(abs(v))) - 1) div 2, -8, 8);
  Result := UnicodeString(FloatToStr(RoundTo(v * power(10, -min(max(t * 3, -24), 24)), -n))) + ' ' + pref[t] + meas;
end;

function GetCompPref(v: Int64; n: Byte): UnicodeString;
var
  t: integer;
const
  //Содержит кратные приставки для данных в Юникоде
  pref: array [0 .. 8] of UnicodeString = ('', #$041A, #$041C, #$0413, #$0422, #$041F, #$042D, #$0417, #$0419);
  prefpost: UnicodeString = #$0438#$0411; //='иБ'
begin
  if InRange(v, 0, 10) then
    Exit(UnicodeString(FloatToStr(v)) + ' ' + pref[0] + prefpost);
  t := EnsureRange(trunc(logN(990, abs(v))), 0, 8);
  Result := UnicodeString(FloatToStr(RoundTo(v * power(2, -min(t * 10, 80)), -n))) + ' ' + pref[t] + prefpost;
end;

end.
