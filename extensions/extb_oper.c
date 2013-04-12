/*
 * Oper extban type: matches opers
 * -- jilles
 *
 */

#include "stdinc.h"
#include "modules.h"
#include "client.h"
#include "ircd.h"
#include "privilege.h"
#include "s_newconf.h" 

static int _modinit(void);
static void _moddeinit(void);
static int eb_oper(const char *data, struct Client *client_p, struct Channel *chptr, long mode_type);

DECLARE_MODULE_AV1(extb_oper, _modinit, _moddeinit, NULL, NULL, NULL, "$Revision: 1299 $");

static int
_modinit(void)
{
	extban_table['o'] = eb_oper;

	return 0;
}

static void
_moddeinit(void)
{
	extban_table['o'] = NULL;
}

static int eb_oper(const char *data, struct Client *client_p,
		struct Channel *chptr, long mode_type)
{

	(void)chptr;
	(void)mode_type;
	
	if (data != NULL)
		/* $o:admin or whatever */
		return HasPrivilege(client_p, data) ? EXTBAN_MATCH : EXTBAN_NOMATCH; 
	return IsOper(client_p) ? EXTBAN_MATCH : EXTBAN_NOMATCH; 
}
