#include "../../../utils/sb.h"
#include "../../support/logger.h"
#include "../generator.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void generateAnimationCompoundStatement(
    Generator generator, AnimationCompoundStatementNode *compoundStatement);

void generateAnimation(Generator generator, AnimationNode *animation);

void generateAnimationParams(Generator generator, AnimationNode *animation);