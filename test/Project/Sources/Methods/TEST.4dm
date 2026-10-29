//%attributes = {}
$devices:=TWAIN Get devices 

$option:=TWAIN Get default option 

$images:=TWAIN Scan ("";$option;Scanner image type PNG)
