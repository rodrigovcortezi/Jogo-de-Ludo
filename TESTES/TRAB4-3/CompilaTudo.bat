@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TestePecas.exe

del *.obj
nmake /Ftestepecas.make 

copy  *.err  tudo.err

notepad tudo.err

popd
