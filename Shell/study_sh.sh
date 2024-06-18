#/bin/bash

if [ $# -lt 1 ] ; then
    echo "\$# is $#"
    echo "arg err"
    exit 1
fi

for var in $@
    do
        echo -n $var
        echo -n ' '
    done
echo ''

array=(111 "aaa" bbb)
for var in ${array[@]}
    do
        echo $var
    done

if [ "bbb" == ${array[2]} ] ; then
    echo "\"bbb\" is equal to \$array[2]"
fi

varCmd="ls $HOME/Code"
echo -e "\tTEST \"ls $HOME/Code\""
if [ -f arg_c ] ; then
    echo -n "ls \$HOME/Code : "
    #echo $($varCmd)
    echo "`${varCmd};`"
fi
echo -e "\tTEST END"

for i in `ls .` ; do
    #` sleep 1 ; echo $i ; `
    ` sleep 1 ; `
    echo -n "$i "
done
echo ''


if [ $1 == "-v" ] ; then
    echo "Test Option Success"
else
    echo "Test Option Failed"
fi

case $2 in
    tmp | temp)
        echo "\$2 is tmp"
        ;;
    apple)
        echo "\$2 is apple"
        ;;
    *)
        echo "NEITHER \$2"
esac


if [ -d "$(pwd)/../test/" ] ; then
    echo "THERE IS A test folder"
fi

cnt=0
while [ $cnt -lt 2 ]
    do
		echo -n "continue (Y/N) "
		read arg_str
		case $arg_str in
		    [Yy0-9] )
		        echo "Yes"
		        ;;
		    [Nn] )
		        echo "No"
		        ;;
		    * )
		        echo "Wrong input"
                ((cnt++))
		esac
    done

ret=$("./arg_c" "999")
while [ $ret -gt 0 ]
    do
        echo "\$ret : $ret"
        echo "\$ret-1 : $((ret-1))"
        ((ret -= 1))
    done

ret=`./arg_c 888`
while [ $ret -gt 0 ]
    do
        echo "\$ret : $ret"
        echo "\$ret-1 : $((ret-1))"
        ((ret -= 1))
    done
