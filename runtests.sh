#!/usr/bin/env bash

didfail=0

for program in test/*.vm; do
    echo -n "${program%.*}: "
    diff <(./stapel ${program}) ${program%.*}.out >/dev/null
    status=$?
    if [ $status -eq 0 ]; then
        echo "[OK]"
    else
        echo "[FAIL]"
        didfail=1
    fi
done

exit $didfail
