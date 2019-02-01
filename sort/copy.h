void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / sizeof(int);
	int byte_loops =  size_e % sizeof(int);
 
	for(int i = 0; i < word_loops; ++i) {
		*(int *)dest = *(int *)src;

		dest += sizeof(int);
		src += sizeof(int);
	}

	for(int i = 0; i < byte_loops; ++i) {
		*(char *)dest = *(char *)src;

		dest += sizeof(char);
		src += sizeof(char);
	}
}
