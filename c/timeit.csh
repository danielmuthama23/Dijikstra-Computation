#!/bin/csh
# 
# Command line: timeit program1 program2 ...
#
# program1, program 2, ... are names of programs to execute on input
# files below

# the array of programs from the commandline
set program = $argv[1]

# adjust as needed
set CPULIMIT = 300
limit cpu $CPULIMIT seconds
limit core 0

# adjust as needed
set inputpath = "/u/cs226/ftp/map"

# input files
set input = (grid5x5.txt        \
             grid25x25.txt      \
             usa-10.txt         \
             usa-100short.txt   \
             usa-100long.txt    \
             usa-5000short.txt  \
             usa-1000long.txt   \
             usa-50000short.txt \
            )


# print header
printf "CPU limit = %d seconds\n\n" $CPULIMIT
printf "%-25s" "Data File"
foreach program ($argv)
    printf "%16s" $program
end
printf "\n"

# print right number of = for table
@ i = 25 + 16 * $#argv 
while ($i > 0)
    printf "="
    @ i = $i - 1
end
printf "\n"


# time it and print out row for each data file and  column for each program
foreach datafile ($input)
    printf "%-25s" $datafile
    if (-f $inputpath/$datafile) then
         foreach program ($argv)
              # printing running time of program on datafile
              # -p flag with time to ensure its output is measured in seconds and not minutes
              /usr/bin/time -p $program <                    \
                   $inputpath/$datafile |&                        \
                   egrep '^user[ ]*[0-9]' |                       \
                   awk '{ if ($2 >= '$CPULIMIT') printf "       CPU limit"; else printf("%16.2f", $2) }'
              # egrep, awk commands extract second column of row corresponding to user time

         end
    else printf "could not open" $datafile
    endif
    printf "\n"
      
end

