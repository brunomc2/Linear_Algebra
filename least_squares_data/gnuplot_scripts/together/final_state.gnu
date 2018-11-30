set encoding utf8
set title "Média total da turma versus nota mínima considerada"
set xlabel "Nota mínima a ser considerada (média das provas)"
set ylabel "Média da turma"
# set xrange [0.0:0.75]
# set yrange [-0.1:1.1]
# unset key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "total_class_average.eps"
plot "db.data" with lines title "Barreira de domínio", "nb.data" with lines title "Sem barreira de domínio", "ind.data" with lines title "Pesos independentes"