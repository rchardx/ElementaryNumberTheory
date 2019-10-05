program lt;
const
maxn = 5000;
var
s:array[0..maxn] of longint;
L,g,c:array[0..maxn] of longint;
n,m,k:longint;
ans,tem:qword;

procedure work;
var
i,j:longint;
begin
ans:=1;
for i:=1 to k do
begin
    c[0]:=1;
    for j:=1 to g[i] do c[j]:=c[j-1]*L[i];
    tem:=0;
    for j:=0 to g[i]-1 do
      tem:=tem+qword(c[j]*(L[i]-1)*(c[g[i]-j-1]));
    tem:=tem+c[g[i]];
    ans:=ans*tem;
end;
writeln(ans);
end;

procedure init;
var
i:longint;
begin
while not eof do
begin
    readln(m);
    k:=0;i:=1;
    while m>1 do
    begin
      if m mod s[i]=0 then
      begin
        inc(k);
        L[k]:=s[i];
        g[k]:=0;
        while m mod s[i]=0 do
        begin
          inc(g[k]);
          m:=m div s[i];
        end;
      end;
      inc(i);
      if (i>n)and(m>1) then
      begin
        inc(k);
        L[k]:=m;
        g[k]:=1;
        break;
      end;
    end;
    work;
end;
end;

function check(k:longint):boolean;
var
i:longint;
begin
for i:=2 to trunc(sqrt(k)) do
if k mod i=0 then exit(false);
exit(true);
end;

procedure prework;
var
i:longint;
begin
n:=0;
for i:=2 to trunc(sqrt(maxlongint)) do
if check(i) then
begin
    inc(n);
    s[n]:=i;
end;
end;

begin
prework;
init;
end.
