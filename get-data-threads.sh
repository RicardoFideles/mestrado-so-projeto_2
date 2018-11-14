#!/bin/bash

./m_thread 500 1 >> threads.csv
./m_thread 1000 1 >> threads.csv
./m_thread 5000 1 >> threads.csv

./m_thread 500 2 >> threads.csv
./m_thread 1000 2 >> threads.csv
./m_thread 5000 2 >> threads.csv

./m_thread 500 3 >> threads.csv
./m_thread 1000 3 >> threads.csv
./m_thread 5000 3 >> threads.csv

./m_thread 500 4 >> threads.csv
./m_thread 1000 4 >> threads.csv
./m_thread 5000 4 >> threads.csv
