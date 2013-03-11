
#include <stdlib.h>

#include "types/types.h"
#include <log/log.h>

#include "device-handler.h"
#include "parser.h"
#include "parser-utils.h"

struct parser __grub2_parser;
struct parser __kboot_parser;
struct parser __native_parser;
struct parser __yaboot_parser;

static const struct parser *const parsers[] = {
//	&__native_parser,
	&__kboot_parser,
	&__grub2_parser,
	&__yaboot_parser,
	NULL
};

void iterate_parsers(struct discover_context *ctx)
{
	int i;
	unsigned int count = 0;

	pb_log("trying parsers for %s\n", ctx->device->device->id);

	for (i = 0; parsers[i]; i++) {
		pb_log("\ttrying parser '%s'\n", parsers[i]->name);
		count += parsers[i]->parse(ctx);
	}
	if (!count)
		pb_log("\tno boot_options found\n");
}

void parser_init(void)
{
}
