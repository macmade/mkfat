/*******************************************************************************
 * Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  -   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *  -   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *  -   Neither the name of 'Jean-David Gadina' nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*!
 * @author          Jean-David Gadina
 * @copyright       (c) 2015, Jean-David Gadina - www.xs-labs.com
 */

#include "Directory.h"
#include "__private/Directory.h"
#include "Display.h"

MutableDirectoryRef DirectoryCreate( DiskRef disk, size_t entryCount )
{
    struct __Directory       * o;
    MutableDirectoryEntryRef * entries;
    MutableDirectoryEntryRef   entry;
    size_t                     i;
    size_t                     j;
    
    if( disk == NULL || entryCount == 0 )
    {
        return NULL;
    }
    
    o       = calloc( sizeof( struct __Directory ), 1 );
    entries = calloc( sizeof( MutableDirectoryEntryRef ), entryCount );
    
    if( o == NULL || entries == NULL )
    {
        free( o );
        free( entries );
        
        DisplayPrintError( "Out of memory" );
        
        return NULL;
    }
    
    o->disk    = disk;
    o->entries = entries;
    
    for( i = 0; i < entryCount; i++ )
    {
        entry = DirectoryEntryCreate( o );
        
        if( entry == NULL )
        {
            for( j = 0; j < i; j++ )
            {
                DirectoryEntryDelete( o->entries[ j ] );
            }
            
            free( entries );
            free( o );
            
            return NULL;
        }
        
        o->entries[ i ] = entry;
    }
    
    return o;
}
