@all: ./builddir/qrl-cpp

./builddir/qrl-cpp: ./builddir
	ninja -C ./builddir

./builddir: meson.build
	meson setup builddir --reconfigure

clean:
	rm -rf builddir

install: ./builddir/qrl-cpp
	install -d $(DESTDIR)/usr/bin
	install ./builddir/qrl-cpp $(DESTDIR)/usr/bin/qrl-cpp

run: ./builddir/qrl-cpp
	./builddir/qrl-cpp
