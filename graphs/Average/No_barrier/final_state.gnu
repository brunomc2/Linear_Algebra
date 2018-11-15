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
plot "../../../least_squares_data/Average/No_barrier/number_of_approved.data" with lines title "Aprovados", "../../../least_squares_data/Average/No_barrier/number_of_fails.data" with lines title "Reprovados", "../../../least_squares_data/Average/No_barrier/number_of_final_exams.data" with lines title "Exames Finais"
