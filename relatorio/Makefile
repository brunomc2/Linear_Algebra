pdf:
	pdflatex *.tex
	biber *.bcf
	pdflatex *.tex
	pdflatex *.tex

silence:
	pdflatex *.tex > /dev/null
	biber *.bcf > /dev/null
	pdflatex *.tex > /dev/null
	pdflatex *.tex > /dev/null

clean:
	rm *.aux \
	*.bbl \
	*.bcf \
	*.blg \
	*.lof \
	*.log \
	*.lot \
	*.run.xml \
	*.toc
