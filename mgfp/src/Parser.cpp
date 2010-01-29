/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   mgflex

#include "Parser.h"

/* User implementation prologue.  */
#line 127 "Parser.ypp"

#include <mgfp/Driver.h>
#include "Scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


/* Line 317 of lalr1.cc.  */
#line 55 "Parser.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace mgf
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 8: /* "\"string\"" */
#line 124 "Parser.ypp"
	{ delete (yyvaluep->stringVal); };
#line 215 "Parser.cpp"
	break;
      case 54: /* "ion" */
#line 125 "Parser.ypp"
	{ delete (yyvaluep->doublepairnode); };
#line 220 "Parser.cpp"
	break;
      case 55: /* "ions" */
#line 125 "Parser.ypp"
	{ delete (yyvaluep->doublepairlistnode); };
#line 225 "Parser.cpp"
	break;
      case 56: /* "charge" */
#line 125 "Parser.ypp"
	{ delete (yyvaluep->integernode); };
#line 230 "Parser.cpp"
	break;
      case 57: /* "charges" */
#line 125 "Parser.ypp"
	{ delete (yyvaluep->integerlistnode); };
#line 235 "Parser.cpp"
	break;
      case 58: /* "csintegerlist" */
#line 125 "Parser.ypp"
	{ delete (yyvaluep->integerlistnode); };
#line 240 "Parser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  Parser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    #line 49 "Parser.ypp"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}
  /* Line 555 of yacc.c.  */
#line 322 "Parser.cpp"
    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:
#line 140 "Parser.ypp"
    { (yyval.doublepairnode) = new DoublePairNode((yysemantic_stack_[(3) - (1)].doubleVal), (yysemantic_stack_[(3) - (2)].doubleVal)); ;}
    break;

  case 3:
#line 141 "Parser.ypp"
    { (yyval.doublepairnode) = new DoublePairNode((yysemantic_stack_[(3) - (1)].integerVal), (yysemantic_stack_[(3) - (2)].doubleVal)); ;}
    break;

  case 4:
#line 142 "Parser.ypp"
    { (yyval.doublepairnode) = new DoublePairNode((yysemantic_stack_[(3) - (1)].doubleVal), (yysemantic_stack_[(3) - (2)].integerVal)); ;}
    break;

  case 5:
#line 143 "Parser.ypp"
    { (yyval.doublepairnode) = new DoublePairNode((yysemantic_stack_[(3) - (1)].integerVal), (yysemantic_stack_[(3) - (2)].integerVal)); ;}
    break;

  case 6:
#line 145 "Parser.ypp"
    { (yyval.doublepairlistnode) = new DoublePairListNode((yysemantic_stack_[(2) - (1)].doublepairlistnode), (yysemantic_stack_[(2) - (2)].doublepairnode)); ;}
    break;

  case 7:
#line 146 "Parser.ypp"
    { (yyval.doublepairlistnode) = new DoublePairListNode((yysemantic_stack_[(1) - (1)].doublepairnode)); ;}
    break;

  case 8:
#line 148 "Parser.ypp"
    { (yyval.integernode) = new IntegerNode((yysemantic_stack_[(2) - (1)].integerVal)); ;}
    break;

  case 9:
#line 149 "Parser.ypp"
    { (yyval.integernode) = new IntegerNode(-(yysemantic_stack_[(2) - (1)].integerVal)); ;}
    break;

  case 10:
#line 151 "Parser.ypp"
    { (yyval.integerlistnode) = (yysemantic_stack_[(3) - (2)].integerlistnode); ;}
    break;

  case 11:
#line 152 "Parser.ypp"
    { (yyval.integerlistnode) = new IntegerListNode((yysemantic_stack_[(3) - (1)].integerlistnode), (yysemantic_stack_[(3) - (3)].integernode)); ;}
    break;

  case 12:
#line 153 "Parser.ypp"
    { (yyval.integerlistnode) = new IntegerListNode((yysemantic_stack_[(3) - (1)].integerlistnode), (yysemantic_stack_[(3) - (3)].integernode)); ;}
    break;

  case 13:
#line 154 "Parser.ypp"
    { (yyval.integerlistnode) = new IntegerListNode((yysemantic_stack_[(1) - (1)].integernode)); ;}
    break;

  case 14:
#line 156 "Parser.ypp"
    { (yyval.integerlistnode) = new IntegerListNode((yysemantic_stack_[(3) - (1)].integerlistnode), (yysemantic_stack_[(3) - (3)].integerVal)); ;}
    break;

  case 15:
#line 157 "Parser.ypp"
    { (yyval.integerlistnode) = new IntegerListNode((yysemantic_stack_[(1) - (1)].integerVal)); ;}
    break;

  case 17:
#line 161 "Parser.ypp"
    {
            driver.context.mgfFile.push_back(driver.context.currentSpectrum);
            driver.context.currentSpectrum.clear();
        ;}
    break;

  case 18:
#line 167 "Parser.ypp"
    {
            driver.context.currentSpectrum.assign(((yysemantic_stack_[(6) - (4)].doublepairlistnode)->pairlist_)->begin(), ((yysemantic_stack_[(6) - (4)].doublepairlistnode)->pairlist_)->end());
            delete (yysemantic_stack_[(6) - (4)].doublepairlistnode); 
        ;}
    break;

  case 21:
#line 175 "Parser.ypp"
    { driver.context.header.setCLE(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 22:
#line 176 "Parser.ypp"
    { driver.context.header.setCOM(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 23:
#line 177 "Parser.ypp"
    { driver.context.header.setDB(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 24:
#line 178 "Parser.ypp"
    { driver.context.header.setFORMAT(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 25:
#line 179 "Parser.ypp"
    { driver.context.header.setINSTRUMENT(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 26:
#line 180 "Parser.ypp"
    { driver.context.header.setIT_MODS(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 27:
#line 181 "Parser.ypp"
    { driver.context.header.setITOLU(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 28:
#line 182 "Parser.ypp"
    { driver.context.header.setMASS(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 29:
#line 183 "Parser.ypp"
    { driver.context.header.setMODS(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 30:
#line 184 "Parser.ypp"
    { driver.context.header.setQUANTITATION(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 31:
#line 185 "Parser.ypp"
    { driver.context.header.setREPORT(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 32:
#line 186 "Parser.ypp"
    { driver.context.header.setREPTYPE(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 33:
#line 187 "Parser.ypp"
    { driver.context.header.setSEARCH(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 34:
#line 188 "Parser.ypp"
    { driver.context.header.setTAXONOMY(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 35:
#line 189 "Parser.ypp"
    { driver.context.header.setTOLU(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 36:
#line 190 "Parser.ypp"
    { /*driver.context.header.setUSER(*$3);*/ delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 37:
#line 191 "Parser.ypp"
    { driver.context.header.setUSEREMAIL(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 38:
#line 192 "Parser.ypp"
    { driver.context.header.setUSERNAME(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 39:
#line 193 "Parser.ypp"
    { driver.context.header.setDECOY(((yysemantic_stack_[(4) - (3)].integerVal))!=0); ;}
    break;

  case 40:
#line 194 "Parser.ypp"
    { driver.context.header.setERRORTOLERANT(((yysemantic_stack_[(4) - (3)].integerVal))!=0); ;}
    break;

  case 41:
#line 195 "Parser.ypp"
    { driver.context.header.setPFA((yysemantic_stack_[(4) - (3)].integerVal)); ;}
    break;

  case 42:
#line 196 "Parser.ypp"
    { driver.context.header.setITOL((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 43:
#line 197 "Parser.ypp"
    { driver.context.header.setITOL((yysemantic_stack_[(4) - (3)].integerVal)); ;}
    break;

  case 44:
#line 198 "Parser.ypp"
    { driver.context.header.setPEP_ISOTOPE_ERROR((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 45:
#line 199 "Parser.ypp"
    { driver.context.header.setPRECURSOR((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 46:
#line 200 "Parser.ypp"
    { driver.context.header.setSEG((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 47:
#line 201 "Parser.ypp"
    { driver.context.header.setTOL((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 48:
#line 202 "Parser.ypp"
    { driver.context.header.setTOL((yysemantic_stack_[(4) - (3)].integerVal)); ;}
    break;

  case 49:
#line 203 "Parser.ypp"
    { driver.context.header.setCHARGE(*((yysemantic_stack_[(4) - (3)].integerlistnode)->integers_)); delete (yysemantic_stack_[(4) - (3)].integerlistnode); ;}
    break;

  case 50:
#line 204 "Parser.ypp"
    { driver.context.header.setFRAMES(*((yysemantic_stack_[(4) - (3)].integerlistnode)->integers_)); delete (yysemantic_stack_[(4) - (3)].integerlistnode); ;}
    break;

  case 54:
#line 210 "Parser.ypp"
    { driver.context.currentSpectrum.setTITLE(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 55:
#line 211 "Parser.ypp"
    { driver.context.currentSpectrum.setCOMP(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 56:
#line 212 "Parser.ypp"
    { driver.context.currentSpectrum.setINSTRUMENT(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 57:
#line 213 "Parser.ypp"
    { driver.context.currentSpectrum.setIT_MODS(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 58:
#line 214 "Parser.ypp"
    { driver.context.currentSpectrum.setRTINSECONDS((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 59:
#line 215 "Parser.ypp"
    { driver.context.currentSpectrum.setSCANS(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 60:
#line 216 "Parser.ypp"
    { driver.context.currentSpectrum.setTOLU(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 61:
#line 217 "Parser.ypp"
    { driver.context.currentSpectrum.setSEQ(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 62:
#line 218 "Parser.ypp"
    { driver.context.currentSpectrum.setTAG(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 63:
#line 219 "Parser.ypp"
    { driver.context.currentSpectrum.setETAG(*(yysemantic_stack_[(4) - (3)].stringVal)); delete (yysemantic_stack_[(4) - (3)].stringVal); ;}
    break;

  case 64:
#line 220 "Parser.ypp"
    { driver.context.currentSpectrum.setTOL((yysemantic_stack_[(4) - (3)].doubleVal)); ;}
    break;

  case 65:
#line 221 "Parser.ypp"
    { driver.context.currentSpectrum.setTOL((yysemantic_stack_[(4) - (3)].integerVal)); ;}
    break;

  case 66:
#line 222 "Parser.ypp"
    { driver.context.currentSpectrum.setCHARGE(*((yysemantic_stack_[(4) - (3)].integerlistnode)->integers_)); delete (yysemantic_stack_[(4) - (3)].integerlistnode); ;}
    break;

  case 67:
#line 223 "Parser.ypp"
    { driver.context.currentSpectrum.setPEPMASS(std::make_pair((yysemantic_stack_[(4) - (3)].doubleVal), 0.0)); ;}
    break;

  case 68:
#line 224 "Parser.ypp"
    { driver.context.currentSpectrum.setPEPMASS(std::make_pair((yysemantic_stack_[(5) - (3)].doubleVal), (yysemantic_stack_[(5) - (4)].doubleVal))); ;}
    break;

  case 69:
#line 225 "Parser.ypp"
    { driver.context.currentSpectrum.setPEPMASS(std::make_pair((yysemantic_stack_[(4) - (3)].integerVal), 0.0)); ;}
    break;

  case 70:
#line 226 "Parser.ypp"
    { driver.context.currentSpectrum.setPEPMASS(std::make_pair((yysemantic_stack_[(5) - (3)].integerVal), (yysemantic_stack_[(5) - (4)].integerVal))); ;}
    break;

  case 72:
#line 231 "Parser.ypp"
    {
             driver.context.mgfFile.setHeader(driver.context.header);
             driver.context.header.clear();
         ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 768 "Parser.cpp"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -70;
  const short int
  Parser::yypact_[] =
  {
       -70,    33,   -70,     8,    39,   -22,    -6,    36,    37,    40,
      41,    42,    43,    44,    45,    46,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    27,   -70,   -70,   -70,     5,    82,    83,
      26,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   127,   128,    32,
     129,   131,   132,   133,   135,   -70,   139,   -70,    -7,     5,
     -70,    -2,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     -70,     2,   -70,   -70,   -70,     1,   -70,   168,   168,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   169,     3,
     -70,   -70,   -70,   -70,   170,    38,    74,    86,   125,   126,
     130,   134,   136,   137,   138,   171,   172,   173,   174,   175,
     -70,    22,   -70,   -70,   176,   177,   178,   180,     5,   179,
     183,   184,   185,    76,   187,   188,   189,   190,   191,    78,
     192,   181,   -70,   -70,   -70,   -70,   -70,    -1,   182,   198,
     199,   200,     9,    28,   201,   202,   203,   204,   205,   206,
     207,   208,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   209,
     -70,   210,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        19,    16,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     1,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72,     0,    17,     0,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,    52,     8,     9,     0,    49,     0,     0,    25,
      26,    48,    47,    35,    21,    22,    23,    24,    27,    28,
      29,    30,    31,    32,    33,    34,    36,    37,    38,    39,
      40,    43,    42,    44,    41,    45,    46,    50,     0,     0,
      10,    12,    11,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     0,    53,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     5,     3,     4,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    66,    55,    63,    56,    57,    69,     0,
      67,     0,    58,    59,    61,    62,    54,    65,    64,    60,
      70,    68
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -70,   -26,   -70,   -21,   -69,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,   160,   161,    70,    71,   101,    33,    67,     1,    34,
     139,   162,     2,     3
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
       105,   106,   203,   107,   107,   137,   107,   144,    35,   145,
     146,    68,   208,   147,   148,   209,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,    65,   145,   146,
      37,   210,    74,    75,   181,   211,    66,     4,    94,    95,
     103,   104,    36,     5,   164,   165,    38,     6,     7,   108,
     108,   140,   108,   138,    69,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     166,   167,   192,   193,   199,   200,   141,   142,    39,    40,
      72,    73,    41,    42,    43,    44,    45,    46,    47,   187,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   182,    96,    97,   168,    98,
      99,   100,   102,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,     0,   163,    68,   143,     0,   169,   170,   183,
     184,   185,   171,   186,   202,   204,   172,   188,   173,   174,
     175,   189,   190,   191,   194,     0,   195,   196,   197,   198,
     201,   205,   206,   207,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   179,   180
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        69,     3,     3,     5,     5,     3,     5,     4,     0,     6,
       7,     6,     3,    10,    11,     6,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,     6,     7,
      52,     3,     6,     7,    12,     7,     9,     4,     6,     7,
      47,    48,     3,    10,     6,     7,    52,    14,    15,    51,
      51,    50,    51,    51,    49,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
       6,     7,     6,     7,     6,     7,   107,   108,    52,    52,
       8,     8,    52,    52,    52,    52,    52,    52,    52,   168,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     6,     6,   161,     7,     6,    52,     7,
       7,     6,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,    -1,    -1,     3,     6,     6,    -1,    52,    52,     3,
       3,     3,    52,     3,     3,     3,    52,     8,    52,    52,
      52,     8,     8,     8,     7,    -1,     8,     8,     8,     8,
       8,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    52,    52,    52,    52
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    61,    65,    66,     4,    10,    14,    15,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    59,    62,     0,     3,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,     0,     9,    60,     6,    49,
      56,    57,     8,     8,     6,     7,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     6,     6,     6,     7,     7,     6,     7,     7,
       6,    58,     3,    47,    48,    57,     3,     5,    51,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,    51,    63,
      50,    56,    56,     6,     4,     6,     7,    10,    11,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      54,    55,    64,     3,     6,     7,     6,     7,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    12,    54,     3,     3,     3,     3,    57,     8,     8,
       8,     8,     6,     7,     7,     8,     8,     8,     8,     6,
       7,     8,     3,     3,     3,     3,     3,     3,     3,     6,
       3,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    43,    45,    40,
      41,    44,    61
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    53,    54,    54,    54,    54,    55,    55,    56,    56,
      57,    57,    57,    57,    58,    58,    59,    59,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    66
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     3,     3,     3,     2,     1,     2,     2,
       3,     3,     3,     1,     3,     1,     0,     2,     6,     0,
       2,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     0,     2,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     5,     4,
       5,     2,     3,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"comment\"", "\"and keyword\"", "\"integer\"", "\"double\"",
  "\"string\"", "\"begin_ions keyword\"", "\"charge set keyword\"",
  "\"amino acid composition keyword\"", "\"end_ions keyword\"",
  "\"error tolerant sequence keyword\"", "\"MS/MS ion series keyword\"",
  "\"variable modifications keyword\"", "\"precursor mass keyword\"",
  "\"retention time or range keyword\"",
  "\"scan number of range keyword\"", "\"amino acid sequence keyword\"",
  "\"sequence tag keyword\"", "\"title keyword\"",
  "\"peptide mass tolerance keyword\"", "\"tolerance units keyword\"",
  "\"enzyme keyword\"", "\"search title keyword\"", "\"database keyword\"",
  "\"MS/MS datafile format keyword\"", "\"units for ITOL keyword\"",
  "\"mass type (mono or avg) keyword\"", "\"fixed modifications keyword\"",
  "\"quantitation method keyword\"", "\"maximum hits keyword\"",
  "\"type of report keyword\"", "\"type of search keyword\"",
  "\"taxonomy keyword\"", "\"user keyword\"", "\"user email keyword\"",
  "\"username keyword\"", "\"perform decoy search keyword\"",
  "\"error tolerance keyword\"", "\"fragment ion tolerance keyword\"",
  "\"misassigned 13C keyword\"", "\"partials keyword\"",
  "\"precursor m/z keyword\"", "\"protein mass (kDa) keyword\"",
  "\"NA translation keyword\"", "'+'", "'-'", "'('", "')'", "','", "'='",
  "$accept", "ion", "ions", "charge", "charges", "csintegerlist", "blocks",
  "block", "globalparams", "globalparam", "localparams", "localparam",
  "contents", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        66,     0,    -1,     7,     7,     3,    -1,     6,     7,     3,
      -1,     7,     6,     3,    -1,     6,     6,     3,    -1,    55,
      54,    -1,    54,    -1,     6,    47,    -1,     6,    48,    -1,
      49,    57,    50,    -1,    57,    51,    56,    -1,    57,     5,
      56,    -1,    56,    -1,    58,    51,     6,    -1,     6,    -1,
      -1,    59,    60,    -1,     9,     3,    63,    55,    12,     3,
      -1,    -1,    61,    62,    -1,    24,    52,     8,     3,    -1,
      25,    52,     8,     3,    -1,    26,    52,     8,     3,    -1,
      27,    52,     8,     3,    -1,    14,    52,     8,     3,    -1,
      15,    52,     8,     3,    -1,    28,    52,     8,     3,    -1,
      29,    52,     8,     3,    -1,    30,    52,     8,     3,    -1,
      31,    52,     8,     3,    -1,    32,    52,     8,     3,    -1,
      33,    52,     8,     3,    -1,    34,    52,     8,     3,    -1,
      35,    52,     8,     3,    -1,    23,    52,     8,     3,    -1,
      36,    52,     8,     3,    -1,    37,    52,     8,     3,    -1,
      38,    52,     8,     3,    -1,    39,    52,     6,     3,    -1,
      40,    52,     6,     3,    -1,    43,    52,     6,     3,    -1,
      41,    52,     7,     3,    -1,    41,    52,     6,     3,    -1,
      42,    52,     7,     3,    -1,    44,    52,     7,     3,    -1,
      45,    52,     7,     3,    -1,    22,    52,     7,     3,    -1,
      22,    52,     6,     3,    -1,    10,    52,    57,     3,    -1,
      46,    52,    58,     3,    -1,     4,     3,    -1,    -1,    63,
      64,    -1,    21,    52,     8,     3,    -1,    11,    52,     8,
       3,    -1,    14,    52,     8,     3,    -1,    15,    52,     8,
       3,    -1,    17,    52,     7,     3,    -1,    18,    52,     8,
       3,    -1,    23,    52,     8,     3,    -1,    19,    52,     8,
       3,    -1,    20,    52,     8,     3,    -1,    13,    52,     8,
       3,    -1,    22,    52,     7,     3,    -1,    22,    52,     6,
       3,    -1,    10,    52,    57,     3,    -1,    16,    52,     7,
       3,    -1,    16,    52,     7,     7,     3,    -1,    16,    52,
       6,     3,    -1,    16,    52,     6,     6,     3,    -1,     4,
       3,    -1,    61,    59,     0,    -1,    65,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     7,    11,    15,    19,    22,    24,    27,
      30,    34,    38,    42,    44,    48,    50,    51,    54,    61,
      62,    65,    70,    75,    80,    85,    90,    95,   100,   105,
     110,   115,   120,   125,   130,   135,   140,   145,   150,   155,
     160,   165,   170,   175,   180,   185,   190,   195,   200,   205,
     210,   215,   218,   219,   222,   227,   232,   237,   242,   247,
     252,   257,   262,   267,   272,   277,   282,   287,   292,   298,
     303,   309,   312,   316
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   140,   140,   141,   142,   143,   145,   146,   148,   149,
     151,   152,   153,   154,   156,   157,   159,   160,   166,   172,
     173,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   207,   208,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   230,   236
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,     2,    47,    51,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 227;
  const int Parser::yynnts_ = 14;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 35;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 53;

  const unsigned int Parser::yyuser_token_number_max_ = 301;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace mgf

#line 238 "Parser.ypp"
 /*** Additional Code ***/

void mgf::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}

