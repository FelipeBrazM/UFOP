# Par�metros gerais
param I := 30;         # N�mero total de enfermeiros
param J := 31;         # N�mero de dias no horizonte de planejamento

# Par�metros dos turnos
param Bp := 4;         # M�nimo de enfermeiros no turno da manh�
param Bs := 4;         # M�nimo de enfermeiros no turno da tarde
param Bm := 4;         # M�nimo de enfermeiros no turno da noite
param Cp := 6;         # M�ximo de enfermeiros no turno da manh�
param Cs := 6;         # M�ximo de enfermeiros no turno da tarde
param Cm := 6;         # M�ximo de enfermeiros no turno da noite

# Par�metros de dias de trabalho
param D := 16;         # M�nimo de dias de trabalho por enfermeiro
param E := 19;         # M�ximo de dias de trabalho por enfermeiro
param Z := 17;         # Dias de trabalho desejados por enfermeiro

# Par�metros de especializa��o
# Define se o enfermeiro i � s�nior (1 = s�nior, 0 = regular)
param senior {i in 1..I} >= 0, <= 1, default 0;
# Define se o enfermeiro i � do sexo masculino (1 = masculino, 0 = feminino)
param male {i in 1..I} >= 0, <= 1, default 0;

# Requisitos m�nimos espec�ficos por turno
param F := 2;          # M�nimo de enfermeiros seniores por turno
param H := 1;          # M�nimo de enfermeiros do sexo masculino por turno

# Vari�veis de decis�o: 1 se o enfermeiro i � designado para o turno em dia j, 0 caso contr�rio
var P {i in 1..I, j in 1..J}, binary;   # Turno da manh�
var S {i in 1..I, j in 1..J}, binary;   # Turno da tarde
var M {i in 1..I, j in 1..J}, binary;   # Turno da noite
var L {i in 1..I, j in 1..J}, binary;   # Folga

# Vari�veis de desvio para as metas
var d1_plus {i in 1..I} >= 0;
var d1_minus {i in 1..I} >= 0;
var d2_plus {i in 1..I} >= 0;
var d2_minus {i in 1..I} >= 0;

# Fun��o objetivo: minimizar os desvios das metas
minimize Total_Deviation:
    sum {i in 1..I} (d1_plus[i] + d1_minus[i] + d2_plus[i] + d2_minus[i]);

# --- Metas (Programa��o por Metas) ---

# Meta 1: Cada enfermeiro deve trabalhar exatamente Z dias
subject to Work_Days_Goal {i in 1..I}:
    sum {j in 1..J} (P[i,j] + S[i,j] + M[i,j]) - Z = d1_plus[i] - d1_minus[i];

# Meta 2: Balanceamento dos turnos � por exemplo, distribui��o equilibrada entre manh�, tarde e noite
# Aqui supomos que, idealmente, o enfermeiro trabalhe 1/3 dos dias em cada turno (ajust�vel conforme a pol�tica)
param ideal_morning := Z / 3;
param ideal_afternoon := Z / 3;
param ideal_night := Z - ideal_morning - ideal_afternoon;

#Meta para o turno da manh�
subject to Shift_Balance_Morning {i in 1..I}:
    sum {j in 1..J} P[i,j] - ideal_morning = d2_plus[i] - d2_minus[i];

# Limite para o desvio da meta 2 (valor ajust�vel)
subject to Limit_Shift_Balance {i in 1..I}:
    d2_plus[i] + d2_minus[i] <= 1;

# --- Restri��es r�gidas de escalonamento ---

# 1. N�mero m�nimo de enfermeiros por turno
subject to Min_Nurses_Morning {j in 1..J}:
    sum {i in 1..I} P[i,j] >= Bp;
subject to Min_Nurses_Afternoon {j in 1..J}:
    sum {i in 1..I} S[i,j] >= Bs;
subject to Min_Nurses_Night {j in 1..J}:
    sum {i in 1..I} M[i,j] >= Bm;

# 2. N�mero m�ximo de enfermeiros por turno
subject to Max_Nurses_Morning {j in 1..J}:
    sum {i in 1..I} P[i,j] <= Cp;
subject to Max_Nurses_Afternoon {j in 1..J}:
    sum {i in 1..I} S[i,j] <= Cs;
subject to Max_Nurses_Night {j in 1..J}:
    sum {i in 1..I} M[i,j] <= Cm;

# 3. Cada enfermeiro deve trabalhar entre D e E dias
subject to Min_Work_Days {i in 1..I}:
    sum {j in 1..J} (P[i,j] + S[i,j] + M[i,j]) >= D;
subject to Max_Work_Days {i in 1..I}:
    sum {j in 1..J} (P[i,j] + S[i,j] + M[i,j]) <= E;

# 4. Um �nico turno por dia
subject to One_Shift_Per_Day {i in 1..I, j in 1..J}:
    P[i,j] + S[i,j] + M[i,j] + L[i,j] = 1;

# 5. Restri��es de sequ�ncia entre turnos (exemplos)
# Ap�s turno da noite, n�o pode ter turno da manh� no dia seguinte
subject to No_Morning_After_Night {i in 1..I, j in 1..J-1}:
    M[i,j] + P[i,j+1] <= 1;
# Ap�s turno da manh�, n�o pode ter turno da noite no dia seguinte
subject to No_Night_After_Morning {i in 1..I, j in 1..J-1}:
    P[i,j] + M[i,j+1] <= 1;
# Ap�s turno da tarde, n�o pode ter turno da manh� no dia seguinte
subject to No_Morning_After_Afternoon {i in 1..I, j in 1..J-1}:
    S[i,j] + P[i,j+1] <= 1;

# 6. Restri��es de folgas consecutivas
subject to Min_Consecutive_Rest {i in 1..I, j in 1..J-2}:
    P[i,j] + S[i,j] + M[i,j] + L[i,j+1] + P[i,j+2] + S[i,j+2] + M[i,j+2] <= 2;
subject to Max_Consecutive_Rest {i in 1..I, j in 1..J-4}:
    L[i,j] + L[i,j+1] + L[i,j+2] + L[i,j+3] + L[i,j+4] <= 4;

# 7. Restri��es de enfermeiros seniores por turno (considerando apenas enfermeiros com senior = 1)
subject to Senior_Nurses_Per_Shift {j in 1..J}:
    sum {i in 1..I: senior[i] = 1} (P[i,j] + S[i,j] + M[i,j]) >= F;

# 8. Restri��es de enfermeiros do sexo masculino por turno
subject to Male_Nurses_Per_Shift {j in 1..J}:
    sum {i in 1..I} male[i] * (P[i,j] + S[i,j] + M[i,j]) >= H;

# 9. Restri��o para n�o ter mais de 1 turno noturno consecutivo (exemplo)
subject to No_Consecutive_Night_Shifts {i in 1..I, j in 1..J-1}:
    M[i,j] + M[i,j+1] <= 1;

# Resolver o modelo
solve;

display {i in 1..I, j in 1..J} P[i,j];
display {i in 1..I, j in 1..J} S[i,j];
display {i in 1..I, j in 1..J} M[i,j];
display {i in 1..I, j in 1..J} L[i,j];

printf "\nEscalonamento de enfermeiros conclu�do!\n";

data;

# Par�metros de especializa��o fornecidos externamente
# Define se o enfermeiro i � s�nior (1 = s�nior, 0 = regular)
param senior :=
   1  1
   2  1
   3  1
   4  1
   5  1
   6  1
   7  1
   8  1
   9  1
  10  1
  11  0
  12  0
  13  0
  14  0
  15  0
  16  0
  17  0
  18  0
  19  0
  20  0
  21  0
  22  0
  23  0
  24  0
  25  0
  26  0
  27  0
  28  0
  29  0
  30  0;

# Define o sexo do enfermeiro: 1 para masculino, 0 para feminino
param male :=
   1  1
   2  1
   3  1
   4  1
   5  1
   6  0
   7  1
   8  0
   9  1
  10  0
  11  1
  12  1
  13  1
  14  0
  15  1
  16  0
  17  1
  18  0
  19  1
  20  0
  21  1
  22  0
  23  1
  24  0
  25  1
  26  0
  27  1
  28  0
  29  1
  30  0;

end;