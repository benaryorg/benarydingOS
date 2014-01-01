void init(void)
{
    const char hw[] = "Hello World!";
    int i;
    char* video = (char*) 0xb8000;
 
    // C-Strings haben ein Nullbyte als Abschluss
    for (i = 0; hw[i] != '\0'; i++) {
 
        // Zeichen i in den Videospeicher kopieren
        video[i * 2] = hw[i];
 
        // 0x07 = Hellgrau auf Schwarz
        video[i * 2 + 1] = 0x07;
    }
}
