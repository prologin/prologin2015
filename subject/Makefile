all: subject.pdf

finale.tex: ../doc/finale.rst
	pandoc -o finale.tex ../doc/finale.rst

api.tex: ../prologin2015.yml
	generator apidoc ../prologin2015.yml .
	mv file.tex api.tex

subject.pdf: subject.tex subject_content.tex useapi.tex finale.tex api.tex prologin2015.pdf image.pdf
	xelatex subject.tex

clean:
	rm -f *.toc
	rm -f *.log
	rm -f *.out
	rm -f *.idx
	rm -f *.aux

distclean: clean
	rm -f api.tex
	rm -f finale.tex
	rm -f *.pdf
