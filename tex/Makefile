.SUFFIXES: .gp .tex .eps .pdf .eps.gz

.eps.pdf:
		epstopdf --outfile $@ $<

.eps.gz.pdf:
		gzip -dc $< | epstopdf --filter > $@

.pdf.eps:
		pdftops -eps $< $@

all:minibwa.pdf

minibwa.pdf:minibwa.tex minibwa.bib
		pdflatex minibwa; bibtex minibwa; pdflatex minibwa; pdflatex minibwa;

clean:
		rm -fr *.toc *.aux *.bbl *.blg *.idx *.log *.out *~ minibwa.pdf
