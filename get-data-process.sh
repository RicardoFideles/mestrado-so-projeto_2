#!/bin/bash

./m_process 500 1  >> process.csv
./m_process 1000 1  >> process.csv
./m_process 5000 1  >> process.csv

./m_process 500 2  >> process.csv
./m_process 1000 2  >> process.csv
./m_process 5000 2  >> process.csv

./m_process 500 3  >> process.csv
./m_process 1000 3  >> process.csv
./m_process 5000 3  >> process.csv

./m_process 500 4  >> process.csv
./m_process 1000 4  >> process.csv
./m_process 5000 4  >> process.csv
