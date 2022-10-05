# Contre-rendue du TP1
## Exercice 5

n = 10000

nb_test = 10000

### somme_prefix1

#### compilation avec -O3

* nbr cycles: 15938 
* nbr secondes: 4.99343e-06
* nbr millisecondes: 0.00499343
* CPI= 1.59388
* IPC= 6.27399e-09

#### compilation avec -O2

* nbr cycles: 57152
* nbr secondes: 1.7906e-05
* nbr millisecondes: 0.017906
* CPI= 5.71527
* IPC= 1.7497e-09

#### compilation avec -O1

* nbr cycles: 51955
* nbr secondes: 1.62738e-05
* nbr millisecondes: 0.0162738
* CPI= 5.19551
* IPC= 1.92474e-09

>meilleur que -02?

#### compilation avec -O0

* nbr cycles: 192703
* nbr secondes: 6.03624e-05
* nbr millisecondes: 0.0603624
* CPI= 19.2704
* IPC= 5.18931e-10

### somme_prefix2
#### compilation avec -03
* nbr cycles: 15703
* nbr secondes: 4.91931e-06
* nbr millisecondes: 0.00491931
* CPI= 1.57033
* IPC= 6.36807e-09

> il n'y a pas d'amélioration notable

## Exercice 6

### poly1

Nombre d'opération de poly1 : 2n mutliplication + n adition = 3n opérations
#### int32

* nbr cycles: 44843
* nbr secondes: 1.40489e-05
* nbr millisecondes: 0.0140489
* CPI= 4.48434
* IPC= 2.22998e-09

#### float64

* nbr cycles: 90020
* nbr secondes: 2.82023e-05
* nbr millisecondes: 0.0282023
* CPI= 9.00207
* IPC= 1.11086e-09

### poly2

Nombre d'opération de poly2 : n mutliplication + n adition = 2n opérations
#### int32
* nbr cycles: 50219
* nbr secondes: 1.5733e-05
* nbr millisecondes: 0.015733
* CPI= 5.02191
* IPC= 1.99128e-09

#### float

* nbr cycles: 132795
* nbr secondes: 4.16029e-05
* nbr millisecondes: 0.0416029
* CPI= 13.2795
* IPC= 7.53039e-10

## Exercice 7

### Reduce plus

* nbr cycles: 12241
* nbr secondes: 3.83511e-06
* nbr millisecondes: 0.00383511
* CPI= 1.22414
* IPC= 8.16901e-09

### Reduce plus 2

* nbr cycles: 2130
* nbr secondes: 6.67505e-07
* nbr millisecondes: 0.000667505
* CPI= 0.213063
* IPC= 4.69345e-08

### Reduce mult 

* nbr cycles: 32155
* nbr secondes: 1.0074e-05
* nbr millisecondes: 0.010074
* CPI= 3.21555
* IPC= 3.10989e-09

### Reduce mult2

* nbr cycles: 11952
* nbr secondes: 3.74431e-06
* nbr millisecondes: 0.00374431
* CPI= 1.19528
* IPC= 8.36624e-09

## Exercice 8

### 1.

* nbr cycles: 433336
* nbr secondes: 0.000130839
* nbr millisecondes: 0.130839
* CPI= 43.3337
* IPC= 2.30768e-10

### 2.

* nbr cycles: 467809
* nbr secondes: 0.000146557
* nbr millisecondes: 0.146557
* CPI= 46.781
* IPC= 2.13762e-10

> Petite amélioration...

### 3.

$ \sin(\frac{2\pi}{3}i) = 0(i\mod3\equiv0),\  \frac{\sqrt{3}}{2}(i\mod3\equiv1) ,\  -\frac{\sqrt{3}}{2}(i\mod3\equiv2)$

* nbr cycles: 80899
* nbr secondes: 2.53442e-05
* nbr millisecondes: 0.0253442
* CPI= 8.08991
* IPC= 1.23611e-09

> On a divisé par ~5.8 le nombre de cycle

### 4.
* nbr cycles: 70982
* nbr secondes: 2.22377e-05
* nbr millisecondes: 0.0222377
* CPI= 7.09827
* IPC= 1.40879e-09

### 4bis.

* nbr cycles: 45782
* nbr secondes: 1.38234e-05
* nbr millisecondes: 0.0138234
* CPI= 4.57828  
* IPC= 2.18422e-09


> On a finalement divisé le nombre de cylce par ~10

## Exercice 9

### poly1_bis
* nbr cycles: 37035
* nbr secondes: 1.11823e-05
* nbr millisecondes: 0.0111823
* CPI= 3.70355
* IPC= 2.70011e-09

> Avec 12 itérations par boucle ça va vite

### poly2_bis

* nbr cycles: 39892
* nbr secondes: 1.20449e-05
* nbr millisecondes: 0.0120449
* CPI= 3.98925
* IPC= 2.50673e-09

> Mieux mais toujours plus lent que l'algo naïf