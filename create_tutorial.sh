eval "$(scramv1 runtime -sh)"
cd - || exit
cd JHUGenMELA/MELA || exit
./setup.sh
eval "$(./setup.sh env standalone)"