all:
# Zip man file
	gzip -k CLI_Timer.1
# Move to man path
		mkdir -p /usr/local/man/man1 
# Will probably exist but just in case
		cp -v CLI_Timer.1.gz /usr/local/man/man1

clean:
	rm CLI_Timer.1.gz

uninstall:
	rm /usr/local/man/man1/CLI_Timer.1.gz