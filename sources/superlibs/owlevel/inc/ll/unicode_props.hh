#pragma once 

namespace ll::Unicode {
    
    enum class block {
                Aegean_Numbers, Alchemical, Alphabetic_PF, Ancient_Greek_Music, Ancient_Greek_Numbers,
                Ancient_Symbols, Arabic, Arabic_Ext_A, Arabic_Math, Arabic_PF_A, Arabic_PF_B, Arabic_Sup,
                Armenian, Arrows, ASCII, Avestan, Balinese, Bamum, Bamum_Sup, Batak, Bengali, Block_Elements,
                Bopomofo, Bopomofo_Ext, Box_Drawing, Brahmi, Braille, Buginese, Buhid, Byzantine_Music,
                Carian, Chakma, Cham, Cherokee, CJK, CJK_Compat, CJK_Compat_Forms, CJK_Compat_Ideographs,
                CJK_Compat_Ideographs_Sup, CJK_Ext_A, CJK_Ext_B, CJK_Ext_C, CJK_Ext_D, CJK_Radicals_Sup,
                CJK_Strokes, CJK_Symbols, Compat_Jamo, Control_Pictures, Coptic, Counting_Rod, Cuneiform,
                Cuneiform_Numbers, Currency_Symbols, Cypriot_Syllabary, Cyrillic, Cyrillic_Ext_A, Cyrillic_Ext_B,
                Cyrillic_Sup, Deseret, Devanagari, Devanagari_Ext, Diacriticals, Diacriticals_For_Symbols,
                Diacriticals_Sup, Dingbats, Domino, Egyptian_Hieroglyphs, Emoticons, Enclosed_Alphanum,
                Enclosed_Alphanum_Sup, Enclosed_CJK, Enclosed_Ideographic_Sup, Ethiopic, Ethiopic_Ext,
                Ethiopic_Ext_A, Ethiopic_Sup, Geometric_Shapes, Georgian, Georgian_Sup, Glagolitic, Gothic, Greek,
                Greek_Ext, Gujarati, Gurmukhi, Half_And_Full_Forms, Half_Marks, Hangul, Hanunoo, Hebrew,
                High_PU_Surrogates, High_Surrogates, Hiragana, IDC, Imperial_Aramaic, Indic_Number_Forms,
                Inscriptional_Pahlavi, Inscriptional_Parthian, IPA_Ext, Jamo, Jamo_Ext_A, Jamo_Ext_B, Javanese,
                Kaithi, Kana_Sup, Kanbun, Kangxi, Kannada, Katakana, Katakana_Ext, Kayah_Li, Kharoshthi, Khmer,
                Khmer_Symbols, Lao, Latin_1_Sup, Latin_Ext_A, Latin_Ext_Additional, Latin_Ext_B, Latin_Ext_C,
                Latin_Ext_D, Lepcha, Letterlike_Symbols, Limbu, Linear_B_Ideograms, Linear_B_Syllabary, Lisu,
                Low_Surrogates, Lycian, Lydian, Mahjong, Malayalam, Mandaic, Math_Alphanum, Math_Operators,
                Meetei_Mayek, Meetei_Mayek_Ext, Meroitic_Cursive, Meroitic_Hieroglyphs, Miao, Misc_Arrows,
                Misc_Math_Symbols_A, Misc_Math_Symbols_B, Misc_Pictographs, Misc_Symbols, Misc_Technical,
                Modifier_Letters, Modifier_Tone_Letters, Mongolian, Music, Myanmar, Myanmar_Ext_A, NB,
                New_Tai_Lue, NKo, Number_Forms, OCR, Ogham, Ol_Chiki, Old_Italic, Old_Persian, Old_South_Arabian,
                Old_Turkic, Oriya, Osmanya, Phags_Pa, Phaistos, Phoenician, Phonetic_Ext, Phonetic_Ext_Sup,
                Playing_Cards, PUA, Punctuation, Rejang, Rumi, Runic, Samaritan, Saurashtra, Sharada, Shavian,
                Sinhala, Small_Forms, Sora_Sompeng, Specials, Sundanese, Sundanese_Sup, Sup_Arrows_A, Sup_Arrows_B,
                Sup_Math_Operators, Sup_PUA_A, Sup_PUA_B, Sup_Punctuation, Super_And_Sub, Syloti_Nagri, Syriac,
                Tagalog, Tagbanwa, Tags, Tai_Le, Tai_Tham, Tai_Viet, Tai_Xuan_Jing, Takri, Tamil, Telugu, Thaana,
                Thai, Tibetan, Tifinagh, Transport_And_Map, UCAS, UCAS_Ext, Ugaritic, Vai, Vedic_Ext,
                Vertical_Forms, VS, VS_Sup, Yi_Radicals, Yi_Syllables, Yijing,
            };
            enum class category : unsigned {
                Lu = 0x1, Ll = 0x2, Lt = 0x4, Lm = 0x8, Lo = 0x10, L = 0x1F,
                Mn = 0x20, Mc = 0x40, Me = 0x80, M = 0xE0,
                Nd = 0x100, Nl = 0x200, No = 0x400, N = 0x700,
                Pc = 0x800, Pd = 0x1000, Ps = 0x2000, Pe = 0x4000, Pi = 0x8000, Pf = 0x10000, Po = 0x20000, P = 0x3F800,
                Sm = 0x40000, Sc = 0x80000, Sk = 0x100000, So = 0x200000, S = 0x3C0000,
                Zs = 0x400000, Zl = 0x800000, Zp = 0x1000000, Z = 0x1C00000,
                Cc = 0x2000000, Cf = 0x4000000, Cs = 0x8000000, Co = 0x10000000, Cn = 0x2000000, C = 0x3E000000,
            };
    
}