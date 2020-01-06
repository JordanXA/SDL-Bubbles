$env:Path += ";D:\mingw64\bin"
$env:Path += ";D:\cmake\bin"

if (Test-Path Makefile) {
  Remove-Item Makefile
}
cmake . -G "MinGW Makefiles"