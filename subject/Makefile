all:: subject.pdf

finale.tex: ../doc/finale.rst
	pandoc -o finale.tex ../doc/finale.rst
	cp ../doc/_static/triangle3.pdf triangle3.pdf

apidoc.tex useapi.tex: ../prologin2015.yml
	generator apidoc ../prologin2015.yml .

subject.pdf:: subject.tex subject_content.tex useapi.tex finale.tex apidoc.tex prologin2015.pdf
	xelatex subject.tex

clean:
	rm -f *.toc
	rm -f *.log
	rm -f *.out
	rm -f *.idx
	rm -f *.aux

distclean: clean
	rm -f apidoc.tex
	rm -f useapi.tex
	rm -f finale.tex
	rm -f subject.pdf

.PHONY: all subject.pdf
