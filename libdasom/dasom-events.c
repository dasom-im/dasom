/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * dasom-events.c
 * This file is part of Dasom.
 *
 * Copyright (C) 2015-2016 Hodong Kim <cogniti@gmail.com>
 *
 * Dasom is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dasom is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dasom-events.h"
#include "dasom-types.h"
#include "dasom-key-syms.h"
#include <string.h>

gboolean
dasom_event_matches (DasomEvent *event, const DasomKey **keys)
{
  g_debug (G_STRLOC ": %s: event->key.state: %d", G_STRFUNC, event->key.state);

  gboolean retval = FALSE;
  gint i;

  /* When pressing Alt key, some programs generate DASOM_META_MASK,
   * while some programs don't generate DASOM_META_MASK.
   * DASOM_MOD2_MASK related to Number key */
  guint mods = event->key.state & (DASOM_MOD2_MASK | DASOM_META_MASK |
                                   DASOM_LOCK_MASK | DASOM_RELEASE_MASK);

  for (i = 0; keys[i] != 0; i++)
  {
    if ((event->key.state & DASOM_MODIFIER_MASK) == (keys[i]->mods | mods) &&
        event->key.keyval == keys[i]->keyval)
    {
      retval = TRUE;
      break;
    }
  }

  return retval;
}

DasomEvent *
dasom_event_new (DasomEventType type)
{
  g_debug (G_STRLOC ": %s", G_STRFUNC);

  DasomEvent *new_event = g_slice_new0 (DasomEvent);
  new_event->type = type;

  return new_event;
}

void
dasom_event_free (DasomEvent *event)
{
  g_debug (G_STRLOC ": %s", G_STRFUNC);

  g_return_if_fail (event != NULL);

  g_slice_free (DasomEvent, event);
}

DasomEvent *
dasom_event_copy (DasomEvent *event)
{
  g_debug (G_STRLOC ": %s", G_STRFUNC);

  g_return_val_if_fail (event != NULL, NULL);

  DasomEvent *new_event;
  new_event = dasom_event_new (DASOM_EVENT_NOTHING);
  *new_event = *event;

  return new_event;
}

G_DEFINE_BOXED_TYPE (DasomEvent, dasom_event, dasom_event_copy, dasom_event_free)
