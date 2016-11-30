::@echo off
:: this is the file to be formatted
echo "file to be formatted"  %1  
echo "file to be formatted"  %2  

echo "astyle.exe path" astyle.exe

echo "call_Artistic_Style.astylerc path" call_Artistic_Style.astylerc 

start astyle/astyle.exe "%1" "%2" --options=astyle/call_Artistic_Style.astylerc

Exit

