set encoding utf8
set title "Distribuição de reprovados/finais/aprovados versus nota mínima considerada"
set xlabel "Nota mínima a ser considerada (média das provas)"
set ylabel "Número de pessoas"
# set xrange [0.0:0.75]
# set yrange [-0.1:1.1]
set key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "final_state.eps"
plot "final_state.data" using 1:2 with lines title "Aprovados", "" using 1:3 with lines title "Exames Finais", "" using 1:4 with lines title "Reprovados"
