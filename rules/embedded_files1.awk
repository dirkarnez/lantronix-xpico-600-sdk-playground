#
# AWK script to generate embedded directory and file declarations from
# a (sorted) list of embedded file names in the form xxx_slash_yyy_...
#
{
    _nc = split($0, components, "_slash_") ;
    _vp = gensub(/(.+)_slash_(.+)/, "\\1", "g") ;

    if (vpath != _vp) {
        oldvpath = vpath ;
        vpath = "" ;
        path = "" ;
        for (n = 1; n < _nc; n++) {
            if (n == 1) {
                vpath = components[n] ;
                path = components[n] ;
            }
            else {
                vpath = vpath"_slash_"components[n] ;
                path = path"/"components[n] ;
            }
            if (vpath != dpath &&
                ( substr(oldvpath, 0, length(vpath)) != vpath ||
                  substr(oldvpath, length(vpath) + 1, 7) != "_slash_")) {

                print "const struct ltrx_embedded_file Embedded_file_"vpath"_contents = {" ;
                print "\""path"/\",\n0,\n\"\"\n};" ;
                dpath = vpath ;
            }
        }
    }
    print "extern const struct ltrx_embedded_file EMBEDDED_FILE_REFERENCE("$0");" ;
}
