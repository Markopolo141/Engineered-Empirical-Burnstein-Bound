g++ -o sim sim.c
./sim 5 50 50
./sim 10 50 50
./sim 25 50 50
./sim 50 50 50
./sim 75 50 50
./sim 100 50 50
./sim 150 50 50
./sim 200 50 50
./sim 300 50 50
./sim 500 50 50
./sim 1000 50 50
./sim 2000 50 50
python gen.py data5_50_50.json
python gen.py data10_50_50.json
python gen.py data25_50_50.json
python gen.py data50_50_50.json
python gen.py data75_50_50.json
python gen.py data100_50_50.json
python gen.py data150_50_50.json
python gen.py data200_50_50.json
python gen.py data300_50_50.json
python gen.py data500_50_50.json
python gen.py data1000_50_50.json
python gen.py data2000_50_50.json