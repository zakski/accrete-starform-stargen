char *engineer_notation(long double, int);
void text_describe_system(planet_pointer, int, long);
void csv_describe_system(FILE *, planet_pointer, int, long);
void csv_thumbnails(FILE*, char*, char*, char*, char*);
char *type_string(planet_type);
void create_svg_file (FILE *, planet_pointer, char *, char *, char *, char *);
FILE *open_csv_file (char *, char *);
FILE *open_html_file(char *, long, char *, char *, char *, char *, char *, FILE *);
void close_html_file(FILE *);
void print_description(FILE *, char *, planet_pointer, char *);
void list_molecules(FILE *, long double);
void html_thumbnails(planet_pointer, FILE *, char *, char *, char *, char *, char *, int, int, int, int, int);
void html_thumbnail_totals(FILE *);
void html_describe_system(planet_pointer, int, char *, FILE *);
void celestia_describe_system(planet_pointer, char *);
char *texture_name (planet_type);

#define STARGEN_URL	"http://www.eldacur.com/~brons/NerdCorner/StarGen/StarGen.html"

// Define the color scheme. Black, Brown and Beige (with a nod to the Duke)

// Main page colors: Beige BG, Dark brown text, Red links
#define BGCOLOR		"#FFCC99"
#define TXCOLOR		"#330000"
#define LINKCOLOR	"#990000"
#define ALINKCOLOR	"#FF0000"

// Contrasting headers: Light brown with black text
#define BGHEADER	"#CC9966"
#define TXHEADER	"#000000"

// Space, background for planets, black with sand colored letters
#define BGSPACE		"#000000"
#define TXSPACE		"#FFE6CC"

// Main table color scheme: Sand with black (space reversed)
#define BGTABLE		"#FFE6CC"
#define TXTABLE		"#000000"

// Notices: Post-It yellow with normal text

#define BGNOTE		"#FFFF66"
#define TXNOTE		TXCOLOR

