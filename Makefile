# SPDX-License-Identifier: GPL-2.0-or-later
WRAPPER=$(DEB_HOST_GNU_TYPE)-cross-exe-wrapper
all:$(WRAPPER) cross-exe-wrapper.1 cross-exe-test
$(WRAPPER):cross-exe-wrapper.in
	sed \
		-e 's/#DEB_HOST_ARCH#/$(DEB_HOST_ARCH)/g' \
		-e 's/#DEB_HOST_MULTIARCH#/$(DEB_HOST_MULTIARCH)/g' \
		$< > $@
	chmod +x $@
cross-exe-wrapper.1:cross-exe-wrapper.in
	pod2man --name cross-exe-wrapper $< > $@
cross-exe-test:cross-exe-test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $<
clean:
	$(RM) -- *-cross-exe-wrapper cross-exe-wrapper.1 cross-exe-test
