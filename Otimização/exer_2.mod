set MP := {1..3}; # Conjunto de matéria prima
set mov := {1..4}; # Conjunto de móveis 

param PV {mov}; # Preço de venda de cada móvel 
param disp {MP}; # Disponibilidade de cada matéria prima
param mat {MP, mov}; # matriz de consumo;

var x {mov}, >= 0, integer;

maximize lucro: sum {j in mov} x[j] * PV[j];

subject to disp_mat_prima{i in MP}: sum{j in mov} x[j] * mat[i, j] <= disp[i];

solve;

data;

param PV := 
 1 100
 2 80
 3 120
 4 20;

param disp := 
 1 250
 2 600 
 3 500;

param mat: 
       1   2   3   4 :=
 1     1   2   1   4
 2     0   1   3   2
 3     3   2   4   0;

end;
