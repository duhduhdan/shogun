#!/bin/bash
if [ -z "${PYTHON}" ]
then
	PYTHON=python
fi

( cd ../src
for e in ../python/examples/*.py
do
	echo -n "running $e .."
	if ${PYTHON} "$e" >/dev/null 2>&1
	then
		echo " passed"
	else
		echo " failed"
	fi
done
)
