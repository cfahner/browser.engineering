/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <stdexcept>
#include <string>

#include "HTMLEntities.h"

namespace HTML::HTMLEntities {

namespace {

constexpr uint64_t hash(std::string_view str) {
    uint64_t hash = 0;
    for (char c : str) {
        hash = (hash * 131) + c;
    }
    return hash;
}

constexpr uint64_t operator"" _hash(const char* str, size_t length) {
    return hash(std::string_view {str, length});
}

}

// Entity names are case sensitive
std::string decode_entity(std::string& entity_name) {
	if (entity_name[0] == '#') {
		try {
			return decode_entity(std::stoi(entity_name.substr(1)));
		} catch (const std::invalid_argument& iae) {
			return entity_name;
		} catch (const std::out_of_range& oore) {
			return entity_name;
		}
	}
	// https://html.spec.whatwg.org/multipage/named-characters.html
	// https://www.w3schools.com/charsets/ref_html_entities_4.asp
	switch (hash(entity_name)) {
		case "quot"_hash: return "\""; // 34
		case "amp"_hash: return "&"; // 38
		case "apos"_hash: return "'"; // 39
		case "lt"_hash: return "<"; // 60
		case "gt"_hash: return ">"; // 62
		case "nbsp"_hash: return " "; // 160
		case "iexcl"_hash: return "¡"; // 161
		case "cent"_hash: return "¢"; // 162
		case "pound"_hash: return "£"; // 163
		case "curren"_hash: return "¤"; // 164
		case "yen"_hash: return "¥"; // 165
		case "brvbar"_hash: return "¦"; // 166
		case "sect"_hash: return "§"; // 167
		case "uml"_hash: return "¨"; // 168
		case "copy"_hash: return "©"; // 169
		case "ordf"_hash: return "ª"; // 170
		case "laquo"_hash: return "ª"; // 171
		case "not"_hash: return "¬"; // 172
		case "shy"_hash: return "­"; // 173
		case "reg"_hash: return "®"; // 174
		case "macr"_hash: return "¯"; // 175
		case "deg"_hash: return "°"; // 176
		case "plusmn"_hash: return "±"; // 177
		case "sup2"_hash: return "²"; // 178
		case "sup3"_hash: return "³"; // 179
		case "acute"_hash: return "´"; // 180
		case "micro"_hash: return "µ"; // 181
		case "para"_hash: return "¶"; // 182
		case "middot"_hash: return "·"; // 183
		case "cedil"_hash: return "¸"; // 184
		case "sup1"_hash: return "¹"; // 185
		case "ordm"_hash: return "º"; // 186
		case "raquo"_hash: return "»"; // 187
		case "frac14"_hash: return "¼"; // 188
		case "frac12"_hash: return "½"; // 189
		case "frac34"_hash: return "¾"; // 190
		case "iquest"_hash: return "¿"; // 191
		case "Agrave"_hash: return "À"; // 192
		case "Aacute"_hash: return "Á"; // 193
		case "Acirc"_hash: return "Â"; // 194
		case "Atilde"_hash: return "Ã"; // 195
		case "Auml"_hash: return "Ä"; // 196
		case "Aring"_hash: return "Å"; // 197
		case "AElig"_hash: return "Æ"; // 198
		case "CCedil"_hash: return "Ç"; // 199
		case "Egrave"_hash: return "È"; // 200
		case "Eacute"_hash: return "É"; // 201
		case "Ecirc"_hash: return "Ê"; // 202
		case "Euml"_hash: return "Ë"; // 203
		case "Igrave"_hash: return "Ì"; // 204
		case "Iacute"_hash: return "Í"; // 205
		case "Icirc"_hash: return "Î"; // 206
		case "Iuml"_hash: return "Ï"; // 207
		case "ETH"_hash: return "Ð"; // 208
		case "Ntilde"_hash: return "Ñ"; // 209
		case "Ograve"_hash: return "Ò"; // 210
		case "Oacute"_hash: return "Ó"; // 211
		case "Ocirc"_hash: return "Ô"; // 212
		case "Otilde"_hash: return "Õ"; // 213
		case "Ouml"_hash: return "Ö"; // 214
		case "times"_hash: return "×"; // 215
		case "Oslash"_hash: return "Ø"; // 216
		case "Ugrave"_hash: return "Ù"; // 217
		case "Uacute"_hash: return "Ú"; // 218
		case "Ucirc"_hash: return "Û"; // 219
		case "Uuml"_hash: return "Ü"; // 220
		case "Yacute"_hash: return "Ý"; // 221
		case "THORN"_hash: return "Þ"; // 222
		case "szlig"_hash: return "ß"; // 223
		case "agrave"_hash: return "à"; // 224
		case "aacute"_hash: return "á"; // 225
		case "acirc"_hash: return "â"; // 226
		case "atilde"_hash: return "ã"; // 227
		case "auml"_hash: return "ä"; // 228
		case "aring"_hash: return "å"; // 229
		case "aelig"_hash: return "æ"; // 230
		case "ccedil"_hash: return "ç"; // 231
		case "egrave"_hash: return "è"; // 232
		case "eacute"_hash: return "é"; // 233
		case "ecirc"_hash: return "ê"; // 234
		case "euml"_hash: return "ë"; // 235
		case "igrave"_hash: return "ì"; // 236
		case "iacute"_hash: return "í"; // 237
		case "icirc"_hash: return "î"; // 238
		case "iuml"_hash: return "ï"; // 239
		case "eth"_hash: return "ð"; // 240
		case "ntilde"_hash: return "ñ"; // 241
		case "ograve"_hash: return "ò"; // 242
		case "oacute"_hash: return "ó"; // 243
		case "ocirc"_hash: return "ô"; // 244
		case "otilde"_hash: return "õ"; // 245
		case "ouml"_hash: return "ö"; // 246
		case "divide"_hash: return "÷"; // 247
		case "oslash"_hash: return "ø"; // 248
		case "ugrave"_hash: return "ù"; // 249
		case "uacute"_hash: return "ú"; // 250
		case "ucirc"_hash: return "û"; // 251
		case "uuml"_hash: return "ü"; // 252
		case "yacute"_hash: return "ý"; // 253
		case "thorn"_hash: return "þ"; // 254
		case "yuml"_hash: return "ÿ"; // 255
		case "fnof"_hash: return "ƒ"; // 402
		case "Alpha"_hash: return "Α"; // 913
		case "Beta"_hash: return "Β"; // 914
		case "Gamma"_hash: return "Γ"; // 915
		case "Delta"_hash: return "Δ"; // 916
		case "Epsilon"_hash: return "Ε"; // 917
		case "Zeta"_hash: return "Ζ"; // 918
		case "Eta"_hash: return "Η"; // 919
		case "Theta"_hash: return "Θ"; // 920
		case "Iota"_hash: return "Ι"; // 921
		case "Kappa"_hash: return "Κ"; // 922
		case "Lambda"_hash: return "Λ"; // 923
		case "Mu"_hash: return "Μ"; // 924
		case "Nu"_hash: return "Ν"; // 925
		case "Xi"_hash: return "Ξ"; // 926
		case "Omicron"_hash: return "Ο"; // 927
		case "Pi"_hash: return "Π"; // 928
		case "Rho"_hash: return "Ρ"; // 929
		case "Sigma"_hash: return "Σ"; // 931
		case "Tau"_hash: return "Τ"; // 932
		case "Upsilon"_hash: return "Υ"; // 933
		case "Phi"_hash: return "Φ"; // 934
		case "Chi"_hash: return "Χ"; // 935
		case "Psi"_hash: return "Ψ"; // 936
		case "Omega"_hash: return "Ω"; // 937
		case "alpha"_hash: return "α"; // 945
		case "beta"_hash: return "β"; // 946
		case "gamma"_hash: return "γ"; // 947
		case "delta"_hash: return "δ"; // 948
		case "epsilon"_hash: return "ε"; // 949
		case "zeta"_hash: return "ζ"; // 950
		case "eta"_hash: return "η"; // 951
		case "theta"_hash: return "θ"; // 952
		case "iota"_hash: return "ι"; // 953
		case "kappa"_hash: return "κ"; // 954
		case "lambda"_hash: return "λ"; // 955
		case "mu"_hash: return "μ"; // 956
		case "nu"_hash: return "ν"; // 957
		case "xi"_hash: return "ξ"; // 958
		case "omicron"_hash: return "ο"; // 959
		case "pi"_hash: return "π"; // 960
		case "rho"_hash: return "ρ"; // 961
		case "sigmaf"_hash: return "ς"; // 962
		case "sigma"_hash: return "σ"; // 963
		case "tau"_hash: return "τ"; // 964
		case "upsilon"_hash: return "υ"; // 965
		case "phi"_hash: return "φ"; // 966
		case "chi"_hash: return "χ"; // 967
		case "psi"_hash: return "ψ"; // 968
		case "omega"_hash: return "ω"; // 969
		case "thetasym"_hash: return "ϑ"; // 977
		case "upsih"_hash: return "ϒ"; // 978
		case "piv"_hash: return "ϖ"; // 982
		case "bull"_hash: return "•"; // 8226
		case "hellip"_hash: return "…"; // 8230
		case "prime"_hash: return "′"; // 8242
		case "Prime"_hash: return "″"; // 8243
		case "oline"_hash: return "‾"; // 8254
		case "frasl"_hash: return "⁄"; // 8260
		case "image"_hash: return "ℑ"; // 8465
		case "weierp"_hash: return "℘"; // 8472
		case "real"_hash: return "ℜ"; // 8476
		case "trade"_hash: return "™"; // 8482
		case "alefsym"_hash: return "ℵ"; // 8501
		case "larr"_hash: return "←"; // 8592
		case "uarr"_hash: return "↑"; // 8593
		case "rarr"_hash: return "→"; // 8594
		case "darr"_hash: return "↓"; // 8595
		case "harr"_hash: return "↔"; // 8596
		case "crarr"_hash: return "↵"; // 8629
		case "lArr"_hash: return "⇐"; // 8656
		case "uArr"_hash: return "⇑"; // 8657
		case "rArr"_hash: return "⇒"; // 8658
		case "dArr"_hash: return "⇓"; // 8659
		case "hArr"_hash: return "⇔"; // 8660
		case "forall"_hash: return "∀"; // 8704
		case "part"_hash: return "∂"; // 8706
		case "exist"_hash: return "∃"; // 8707
		case "empty"_hash: return "∅"; // 8709
		case "nabla"_hash: return "∇"; // 8711
		case "isin"_hash: return "∈"; // 8712
		case "notin"_hash: return "∉"; // 8713
		case "ni"_hash: return "∋"; // 8715
		case "prod"_hash: return "∏"; // 8719
		case "sum"_hash: return "∑"; // 8721
		case "minus"_hash: return "−"; // 8722
		case "lowast"_hash: return "∗"; // 8727
		case "radic"_hash: return "√"; // 8730
		case "prop"_hash: return "∝"; // 8733
		case "infin"_hash: return "∞"; // 8734
		case "ang"_hash: return "∠"; // 8736
		case "and"_hash: return "∧"; // 8743
		case "or"_hash: return "∨"; // 8744
		case "cap"_hash: return "∩"; // 8745
		case "cup"_hash: return "∪"; // 8746
		case "int"_hash: return "∫"; // 8747
		case "there4"_hash: return "∴"; // 8756
		case "sim"_hash: return "∼"; // 8764
		case "cong"_hash: return "≅"; // 8773
		case "asymp"_hash: return "≈"; // 8776
		case "ne"_hash: return "≠"; // 8800
		case "equiv"_hash: return "≡"; // 8801
		case "le"_hash: return "≤"; // 8804
		case "ge"_hash: return "≥"; // 8805
		case "sub"_hash: return "⊂"; // 8834
		case "sup"_hash: return "⊃"; // 8835
		case "nsub"_hash: return "⊄"; // 8836
		case "sube"_hash: return "⊆"; // 8838
		case "supe"_hash: return "⊇"; // 8839
		case "oplus"_hash: return "⊕"; // 8853
		case "otimes"_hash: return "⊗"; // 8855
		case "perp"_hash: return "⊥"; // 8869
		case "sdot"_hash: return "⋅"; // 8901
		case "lceil"_hash: return "⌈"; // 8968
		case "rceil"_hash: return "⌉"; // 8969
		case "lfloor"_hash: return "⌊"; // 8970
		case "rfloor"_hash: return "⌋"; // 8971
		case "lang"_hash: return "〈"; // 9001
		case "rang"_hash: return "〉"; // 9002
		case "loz"_hash: return "◊"; // 9674
		case "spades"_hash: return "♠"; // 9824
		case "clubs"_hash: return "♣"; // 9827
		case "hearts"_hash: return "♥"; // 9829
		case "diams"_hash: return "♦"; // 9830
	}
	return "�";
}

std::string decode_entity(int entity_number) {
	switch (entity_number) {
		case 32: return " ";
		case 33: return "!";
		case 34: return "\"";
		case 35: return "#";
		case 36: return "$";
		case 37: return "%";
		case 38: return "&";
		case 39: return "'";
		case 40: return "(";
		case 41: return ")";
		case 42: return "*";
		case 43: return "+";
		case 44: return ",";
		case 45: return "-";
		case 46: return ".";
		case 47: return "/";
		case 48: return "0";
		case 49: return "1";
		case 50: return "2";
		case 51: return "3";
		case 52: return "4";
		case 53: return "5";
		case 54: return "6";
		case 55: return "7";
		case 56: return "8";
		case 57: return "9";
		case 58: return ":";
		case 59: return ";";
		case 60: return "<";
		case 61: return "=";
		case 62: return ">";
		case 63: return "?";
		case 64: return "@";
		case 65: return "A";
		case 66: return "B";
		case 67: return "C";
		case 68: return "D";
		case 69: return "E";
		case 70: return "F";
		case 71: return "G";
		case 72: return "H";
		case 73: return "I";
		case 74: return "J";
		case 75: return "K";
		case 76: return "L";
		case 77: return "M";
		case 78: return "N";
		case 79: return "O";
		case 80: return "P";
		case 81: return "Q";
		case 82: return "R";
		case 83: return "S";
		case 84: return "T";
		case 85: return "U";
		case 86: return "V";
		case 87: return "W";
		case 88: return "X";
		case 89: return "Y";
		case 90: return "Z";
		case 91: return "[";
		case 92: return "\\";
		case 93: return "]";
		case 94: return "^";
		case 95: return "_";
		case 96: return "`";
		case 97: return "a";
		case 98: return "b";
		case 99: return "c";
		case 100: return "d";
		case 101: return "e";
		case 102: return "f";
		case 103: return "g";
		case 104: return "h";
		case 105: return "i";
		case 106: return "j";
		case 107: return "k";
		case 108: return "l";
		case 109: return "m";
		case 110: return "n";
		case 111: return "o";
		case 112: return "p";
		case 113: return "q";
		case 114: return "r";
		case 115: return "s";
		case 116: return "t";
		case 117: return "u";
		case 118: return "v";
		case 119: return "w";
		case 120: return "x";
		case 121: return "y";
		case 122: return "z";
		case 123: return "{";
		case 124: return "|";
		case 125: return "}";
		case 126: return "~";
		case 160: return " ";
		case 161: return "¡";
		case 162: return "¢";
		case 163: return "£";
		case 164: return "¤";
		case 165: return "¥";
		case 166: return "¦";
		case 167: return "§";
		case 168: return "¨";
		case 169: return "©";
		case 170: return "ª";
		case 171: return "«";
		case 172: return "¬";
		case 173: return "­";
		case 174: return "­®";
		case 175: return "­¯";
		case 176: return "­°";
		case 177: return "±";
		case 178: return "²";
		case 179: return "³";
		case 180: return "´";
		case 181: return "µ";
		case 182: return "¶";
		case 183: return "·";
		case 184: return "¸";
		case 185: return "¹";
		case 186: return "º";
		case 187: return "»";
		case 188: return "¼";
		case 189: return "½";
		case 190: return "¾";
		case 191: return "¿";
		case 192: return "À";
		case 193: return "Á";
		case 194: return "Â";
		case 195: return "Ã";
		case 196: return "Ä";
		case 197: return "Å";
		case 198: return "Æ";
		case 199: return "Ç";
		case 200: return "È";
		case 201: return "É";
		case 202: return "Ê";
		case 203: return "Ë";
		case 204: return "Ì";
		case 205: return "Í";
		case 206: return "Î";
		case 207: return "Ï";
		case 208: return "Ð";
		case 209: return "Ñ";
		case 210: return "Ò";
		case 211: return "Ó";
		case 212: return "Ô";
		case 213: return "Õ";
		case 214: return "Ö";
		case 215: return "×";
		case 216: return "Ø";
		case 217: return "Ù";
		case 218: return "Ú";
		case 219: return "Û";
		case 220: return "Ü";
		case 221: return "Ý";
		case 222: return "Þ";
		case 223: return "ß";
		case 224: return "à";
		case 225: return "á";
		case 226: return "â";
		case 227: return "ã";
		case 228: return "ä";
		case 229: return "å";
		case 230: return "æ";
		case 231: return "ç";
		case 232: return "è";
		case 233: return "é";
		case 234: return "ê";
		case 235: return "ë";
		case 236: return "ì";
		case 237: return "í";
		case 238: return "î";
		case 239: return "ï";
		case 240: return "ð";
		case 241: return "ñ";
		case 242: return "ò";
		case 243: return "ó";
		case 244: return "ô";
		case 245: return "õ";
		case 246: return "ö";
		case 247: return "÷";
		case 248: return "ø";
		case 249: return "ù";
		case 250: return "ú";
		case 251: return "û";
		case 252: return "ü";
		case 253: return "ý";
		case 254: return "þ";
		case 255: return "ÿ";
		case 402: return "ƒ";
		case 913: return "Α";
		case 914: return "Β";
		case 915: return "Γ";
		case 916: return "Δ";
		case 917: return "Ε";
		case 918: return "Ζ";
		case 919: return "Η";
		case 920: return "Θ";
		case 921: return "Ι";
		case 922: return "Κ";
		case 923: return "Λ";
		case 924: return "Μ";
		case 925: return "Ν";
		case 926: return "Ξ";
		case 927: return "Ο";
		case 928: return "Π";
		case 929: return "Ρ";
		case 931: return "Σ";
		case 932: return "Τ";
		case 933: return "Υ";
		case 934: return "Φ";
		case 935: return "Χ";
		case 936: return "Ψ";
		case 937: return "Ω";
		case 945: return "α";
		case 946: return "β";
		case 947: return "γ";
		case 948: return "δ";
		case 949: return "ε";
		case 950: return "ζ";
		case 951: return "η";
		case 952: return "θ";
		case 953: return "ι";
		case 954: return "κ";
		case 955: return "λ";
		case 956: return "μ";
		case 957: return "ν";
		case 958: return "ξ";
		case 959: return "ο";
		case 960: return "π";
		case 961: return "ρ";
		case 962: return "ς";
		case 963: return "σ";
		case 964: return "τ";
		case 965: return "υ";
		case 966: return "φ";
		case 967: return "χ";
		case 968: return "ψ";
		case 969: return "ω";
		case 977: return "ϑ";
		case 978: return "ϒ";
		case 982: return "ϖ";
		case 8226: return "•";
		case 8230: return "…";
		case 8242: return "′";
		case 8243: return "″";
		case 8254: return "‾";
		case 8260: return "⁄";
		case 8465: return "ℑ";
		case 8472: return "℘";
		case 8476: return "ℜ";
		case 8482: return "™";
		case 8501: return "ℵ";
		case 8592: return "←";
		case 8593: return "↑";
		case 8594: return "→";
		case 8595: return "↓";
		case 8596: return "↔";
		case 8629: return "↵";
		case 8656: return "⇐";
		case 8657: return "⇑";
		case 8658: return "⇒";
		case 8659: return "⇓";
		case 8660: return "⇔";
		case 8704: return "∀";
		case 8706: return "∂";
		case 8707: return "∃";
		case 8709: return "∅";
		case 8711: return "∇";
		case 8712: return "∈";
		case 8713: return "∉";
		case 8715: return "∋";
		case 8719: return "∏";
		case 8721: return "∑";
		case 8722: return "−";
		case 8727: return "∗";
		case 8730: return "√";
		case 8733: return "∝";
		case 8734: return "∞";
		case 8736: return "∠";
		case 8743: return "∧";
		case 8744: return "∨";
		case 8745: return "∩";
		case 8746: return "∪";
		case 8747: return "∫";
		case 8756: return "∴";
		case 8764: return "∼";
		case 8773: return "≅";
		case 8776: return "≈";
		case 8800: return "≠";
		case 8801: return "≡";
		case 8804: return "≤";
		case 8805: return "≥";
		case 8834: return "⊂";
		case 8835: return "⊃";
		case 8836: return "⊄";
		case 8838: return "⊆";
		case 8839: return "⊇";
		case 8853: return "⊕";
		case 8855: return "⊗";
		case 8869: return "⊥";
		case 8901: return "⋅";
		case 8968: return "⌈";
		case 8969: return "⌉";
		case 8970: return "⌊";
		case 8971: return "⌋";
		case 9001: return "〈";
		case 9002: return "〉";
		case 9674: return "◊";
		case 9824: return "♠";
		case 9827: return "♣";
		case 9829: return "♥";
		case 9830: return "♦";
	}
	return "�";
}

}
