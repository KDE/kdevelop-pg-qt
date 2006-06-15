/***************************************************************************
 *   Copyright (C) 2006 by Jakob Petsovits                                 *
 *   jpetso@gmx.at                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef CSHARP_PP_SCOPE_H
#define CSHARP_PP_SCOPE_H

class csharp;


class csharp_pp_scope
{
public:
    enum scope_type {
      type_root,
      type_if,
      type_region
    };

    csharp_pp_scope( csharp* parser );
    ~csharp_pp_scope();

    /**
     * Retrieves the last child of the scope hierarchy. That child contains
     * the state at the current code position and should be used for getting
     * info.
     */
    csharp_pp_scope* current_scope();

    csharp_pp_scope::scope_type type();

    /**
     * Returns @true if the code at the current position is included into
     * the parser's token stream, or @false if it's a skipped section.
     */
    bool is_active();

    /**
     * Returns @true if the scope corresponds to an #if/#elif/#else condition
     * and has not yet seen a code segment that is included
     * (as in: not skipped), and @false otherwise.
     */
    bool is_waiting_for_active_section();

    /**
     * Set the current state of the scope to "active" or "not active".
     * To be called for #if and #elif conditions with the expression value
     * as argument.
     */
    void set_activated( bool active );

    /**
     * Creates a new child scope inside this one, inheriting its state.
     *
     * @param type  Determines the type of the new scope.
     * @param new_current  The new current scope, given as a return value.
     * @return  @true if the scope has been created, or @false if this scope
     *          already possesses a child (in this case, nothing is done).
     */
    bool push_scope( csharp_pp_scope::scope_type type, csharp_pp_scope** new_current = 0 );

    /**
     * Destroys this scope so that its parent is the current scope again.
     * If this one is already the root scope, it is not destroyed and stays
     * the currently active scope.
     *
     * @param type  The type of the scope that should be closed.
     *              If it doesn't match with this scope's type,
     *              it's semantically wrong and the scope is not destroyed.
     * @param new_current  The new current scope, given as a return value.
     * @return  @true if the scope has been destroyed,
     *          @false if it is already the root scope.
     */
    bool pop_scope( csharp_pp_scope::scope_type type, csharp_pp_scope** new_current = 0 );

    /**
     * Sets the actual parser class - the one not handling the pre-processor.
     */
    void set_parser( csharp* parser );
    csharp* parser();

private:
    csharp_pp_scope( csharp_pp_scope::scope_type type, csharp* parser, bool active );

    void set_parent( csharp_pp_scope* parent );
    csharp_pp_scope* parent();

    scope_type _M_type;
    csharp* _M_parser;

    /** Child scope of the current one. (May be recursive.) */
    csharp_pp_scope* _M_child;

    /** Parent scope of the current one. */
    csharp_pp_scope* _M_parent;

    bool _M_is_active;

    /** This flag is initially set true, and becomes false when an #if or
     *  #elif expression is found that evaluates to true. */
    bool _M_waiting_for_active_section;
};

#endif // CSHARP_PP_SCOPE_H