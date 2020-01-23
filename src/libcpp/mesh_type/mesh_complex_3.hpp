
    /*
    --------------------------------------------------------
     * MESH-COMPLEX-3: piecewise mixed complex in R^3. 
    --------------------------------------------------------
     *
     * This program may be freely redistributed under the 
     * condition that the copyright notices (including this 
     * entire header) are not removed, and no compensation 
     * is received through use of the software.  Private, 
     * research, and institutional use is free.  You may 
     * distribute modified versions of this code UNDER THE 
     * CONDITION THAT THIS CODE AND ANY MODIFICATIONS MADE 
     * TO IT IN THE SAME FILE REMAIN UNDER COPYRIGHT OF THE 
     * ORIGINAL AUTHOR, BOTH SOURCE AND OBJECT CODE ARE 
     * MADE FREELY AVAILABLE WITHOUT CHARGE, AND CLEAR 
     * NOTICE IS GIVEN OF THE MODIFICATIONS.  Distribution 
     * of this code as part of a commercial system is 
     * permissible ONLY BY DIRECT ARRANGEMENT WITH THE 
     * AUTHOR.  (If you are not directly supplying this 
     * code to a customer, and you are instead telling them 
     * how they can obtain it for free, then you are not 
     * required to make any arrangement with me.) 
     *
     * Disclaimer:  Neither I nor: Columbia University, The
     * Massachusetts Institute of Technology, The 
     * University of Sydney, nor The National Aeronautics
     * and Space Administration warrant this code in any 
     * way whatsoever.  This code is provided "as-is" to be 
     * used at your own risk.
     *
    --------------------------------------------------------
     *
     * Last updated: 09 November, 2019
     *
     * Copyright 2013-2019
     * Darren Engwirda
     * de2363@columbia.edu
     * https://github.com/dengwirda/
     *
    --------------------------------------------------------
     */

#   pragma once

#   ifndef __MESH_COMPLEX_3__
#   define __MESH_COMPLEX_3__

    namespace mesh {

    /*
    --------------------------------------------------------
     * MESH-COMPLEX-3 generic mixed-cell 3-complex.
    --------------------------------------------------------
     * NODE-TYPE - 0-face type + coord.'s
     * EDGE-TYPE - 1-face type
     * TRI3-TYPE - 2-face type
     * QUAD-TYPE - 2-face type
     * TRI4-TYPE - 3-face type
     * HEXA-TYPE - 3-face type
     * PYRA-TYPE - 3-face type
     * WEDG-TYPE - 3-face type
     * ALLOCATOR - memory allocator
    --------------------------------------------------------
     */
        
    template <
    typename NN ,
    typename E2 ,
    typename T3 ,
    typename Q4 ,
    typename T4 ,
    typename H8 ,
    typename P5 , 
    typename W6 ,
    typename AA = allocators::basic_alloc 
             >
    class mesh_complex_3
    {
/*----------------------------------- mesh-complex in R^3 */
    public  :
    typedef NN                          node_type ;
    typedef E2                          edge_type ;
    typedef T3                          tri3_type ;
    typedef Q4                          quad_type ;
    typedef T4                          tri4_type ;
    typedef H8                          hexa_type ;
    typedef P5                          pyra_type ;
    typedef W6                          wedg_type ;
    typedef AA                          allocator ;

    typedef typename 
            node_type::real_type        real_type ;
    typedef typename 
            edge_type::iptr_type        iptr_type ;
    typedef typename
            allocator::size_type        size_type ;

    iptr_type static constexpr _dims = +3 ;

    typedef containers::block_array <
                node_type, 
                allocator           >   node_list ;

    typedef containers::block_array <
                edge_type, 
                allocator           >   edge_list ;

    typedef containers::block_array <
                tri3_type, 
                allocator           >   tri3_list ;

    typedef containers::block_array <
                quad_type, 
                allocator           >   quad_list ;
                
    typedef containers::block_array <
                tri4_type, 
                allocator           >   tri4_list ;

    typedef containers::block_array <
                hexa_type, 
                allocator           >   hexa_list ;

    typedef containers::block_array <
                pyra_type, 
                allocator           >   pyra_list ;

    typedef containers::block_array <
                wedg_type, 
                allocator           >   wedg_list ;

    typedef containers::array       <
                iptr_type, 
                allocator           >   iptr_list ;
    
    #define __hashscal sizeof(iptr_type)/sizeof(uint32_t)

    class node_hash
        {
        public  :
        __const_ptr(node_list) _nset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call node_hash  (
            node_list *_nsrc
            ) : _nset( _nsrc) {}
    /*----------------------- hash node indexing for node */
        __inline_call 
            uint32_t  operator() (
            iptr_type _npos
            ) const
        {
            return this->_nset->
                operator[](_npos).node( 0) ;
        }
        } ;

    class edge_hash
        {
        public  :
        __const_ptr(edge_list) _eset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call edge_hash  (
            edge_list *_esrc
            ) : _eset( _esrc) {}
    /*----------------------- hash node indexing for edge */
        __inline_call 
            uint32_t  operator() (
            iptr_type _epos
            ) const
        {
            iptr_type _enod[2];
            _enod[0] = this->_eset->
                operator[](_epos).node( 0) ;
            _enod[1] = this->_eset->
                operator[](_epos).node( 1) ;

            algorithms::isort (
                &_enod[0], &_enod[2] , 
                    std::less<iptr_type>());
            
            return hash::hashword (
                (uint32_t*)&_enod[0] ,
                    +2 * __hashscal, +137) ;
        }
        } ;
        
    class tri3_hash
        {
        public  :
        __const_ptr(tri3_list) _tset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call tri3_hash  (
            tri3_list *_tsrc
            ) : _tset( _tsrc) {}
    /*----------------------- hash node indexing for face */
        __inline_call 
            uint32_t  operator() (
            iptr_type _tpos
            ) const
        {
            iptr_type _tnod[3];
            _tnod[0] = this->_tset->
                operator[](_tpos).node( 0) ;
            _tnod[1] = this->_tset->
                operator[](_tpos).node( 1) ;
            _tnod[2] = this->_tset->
                operator[](_tpos).node( 2) ;

            algorithms::isort (
                &_tnod[0], &_tnod[3] , 
                    std::less<iptr_type>());
            
            return hash::hashword (
                (uint32_t*)&_tnod[0] ,
                    +3 * __hashscal, +137) ;
        }
        } ;
        
    class tri4_hash
        {
        public  :
        __const_ptr(tri4_list) _tset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call tri4_hash  (
            tri4_list *_tsrc
            ) : _tset( _tsrc) {}
    /*----------------------- hash node indexing for face */
        __inline_call 
            uint32_t  operator() (
            iptr_type _tpos
            ) const
        {
            iptr_type _tnod[4];
            _tnod[0] = this->_tset->
                operator[](_tpos).node( 0) ;
            _tnod[1] = this->_tset->
                operator[](_tpos).node( 1) ;
            _tnod[2] = this->_tset->
                operator[](_tpos).node( 2) ;
            _tnod[3] = this->_tset->
                operator[](_tpos).node( 3) ;

            algorithms::isort (
                &_tnod[0], &_tnod[4] , 
                    std::less<iptr_type>());
            
            return hash::hashword (
                (uint32_t*)&_tnod[0] ,
                    +4 * __hashscal, +137) ;
        }
        } ;
        
 
    class node_pred
        {
        public  :
        __const_ptr(node_list) _nset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call node_pred  (
            node_list *_nsrc
            ) : _nset( _nsrc) {}
    /*----------------------- compute "equal-to" for node */
        __inline_call 
            bool_type operator() (
            iptr_type _ipos,
            iptr_type _jpos
            ) const
        {
            iptr_type _inod[1];
            _inod[0] = this->_nset->
                operator[](_ipos).node( 0) ;
                
            iptr_type _jnod[1];
            _jnod[0] = this->_nset->
                operator[](_jpos).node( 0) ;
            
            return _inod[0] == _jnod[0]  ;
        }
        } ;
 
    class edge_pred
        {
        public  :
        __const_ptr(edge_list) _eset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call edge_pred  (
            edge_list *_esrc
            ) : _eset( _esrc) {}
    /*----------------------- compute "equal-to" for edge */
        __inline_call 
            bool_type operator() (
            iptr_type _ipos,
            iptr_type _jpos
            ) const
        {
            iptr_type _inod[2];
            _inod[0] = this->_eset->
                operator[](_ipos).node( 0) ;
            _inod[1] = this->_eset->
                operator[](_ipos).node( 1) ;
                
            iptr_type _jnod[2];
            _jnod[0] = this->_eset->
                operator[](_jpos).node( 0) ;
            _jnod[1] = this->_eset->
                operator[](_jpos).node( 1) ;

            algorithms::isort (
                &_inod[0], &_inod[2], 
                    std::less<iptr_type>());

            algorithms::isort (
                &_jnod[0], &_jnod[2], 
                    std::less<iptr_type>());
            
            return _inod[0] == _jnod[0] &&
                   _inod[1] == _jnod[1]  ;
        }
        } ;
        
    class tri3_pred
        {
        public  :
        __const_ptr(tri3_list) _tset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call tri3_pred  (
            tri3_list *_tsrc
            ) : _tset( _tsrc) {}
    /*----------------------- compute "equal-to" for face */
        __inline_call 
            bool_type operator() (
            iptr_type _ipos,
            iptr_type _jpos
            ) const
        {
            iptr_type _inod[3];
            _inod[0] = this->_tset->
                operator[](_ipos).node( 0) ;
            _inod[1] = this->_tset->
                operator[](_ipos).node( 1) ;
            _inod[2] = this->_tset->
                operator[](_ipos).node( 2) ;
                
            iptr_type _jnod[3];
            _jnod[0] = this->_tset->
                operator[](_jpos).node( 0) ;
            _jnod[1] = this->_tset->
                operator[](_jpos).node( 1) ;
            _jnod[2] = this->_tset->
                operator[](_jpos).node( 2) ;

            algorithms::isort (
                &_inod[0], &_inod[3], 
                    std::less<iptr_type>());

            algorithms::isort (
                &_jnod[0], &_jnod[3], 
                    std::less<iptr_type>());
            
            return _inod[0] == _jnod[0] &&
                   _inod[1] == _jnod[1] &&
                   _inod[2] == _jnod[2]  ;
        }
        } ;
        
    class tri4_pred
        {
        public  :
        __const_ptr(tri4_list) _tset ;    
        public  :
    /*----------------------- build hash _obj. from _src. */
        __inline_call tri4_pred  (
            tri4_list *_tsrc
            ) : _tset( _tsrc) {}
    /*----------------------- compute "equal-to" for face */
        __inline_call 
            bool_type operator() (
            iptr_type _ipos,
            iptr_type _jpos
            ) const
        {
            iptr_type _inod[4];
            _inod[0] = this->_tset->
                operator[](_ipos).node( 0) ;
            _inod[1] = this->_tset->
                operator[](_ipos).node( 1) ;
            _inod[2] = this->_tset->
                operator[](_ipos).node( 2) ;
            _inod[3] = this->_tset->
                operator[](_ipos).node( 3) ;
                
            iptr_type _jnod[4];
            _jnod[0] = this->_tset->
                operator[](_jpos).node( 0) ;
            _jnod[1] = this->_tset->
                operator[](_jpos).node( 1) ;
            _jnod[2] = this->_tset->
                operator[](_jpos).node( 2) ;
            _jnod[3] = this->_tset->
                operator[](_jpos).node( 3) ;

            algorithms::isort (
                &_inod[0], &_inod[4], 
                    std::less<iptr_type>());

            algorithms::isort (
                &_jnod[0], &_jnod[4], 
                    std::less<iptr_type>());
            
            return _inod[0] == _jnod[0] &&
                   _inod[1] == _jnod[1] &&
                   _inod[2] == _jnod[2] &&
                   _inod[3] == _jnod[3]  ;
        }
        } ;
        
    #undef __hashscal

    iptr_type static const pool_byte_size=96*1024 ;

    typedef allocators::_pool_alloc <
            allocators::basic_alloc ,
                pool_byte_size      >   pool_base ;

    typedef allocators::_wrap_alloc <
                pool_base           >   pool_wrap ;

  //typedef containers::hash_table  <
  //            iptr_type, 
  //            node_hash, 
  //            node_pred,
  //            pool_wrap>              node_maps ;

    typedef containers::hash_table  <
                iptr_type, 
                edge_hash, 
                edge_pred,
                pool_wrap>              edge_maps ;
                
    typedef containers::hash_table  <
                iptr_type, 
                tri3_hash, 
                tri3_pred,
                pool_wrap>              tri3_maps ;
                
    typedef containers::hash_table  <
                iptr_type, 
                tri4_hash, 
                tri4_pred,
                pool_wrap>              tri4_maps ;
                
    typedef containers::array_list  <
                iptr_type,
                pool_wrap           >   conn_list ;

    public  :

    pool_base                   _hsrc ;
    pool_base                   _csrc ;
    
    conn_list                   _N1E2 ;
    conn_list                   _E2T3 ;
    conn_list                   _E2Q4 ;
    conn_list                   _T3T4 ;
    conn_list                   _T3P5 ;
    conn_list                   _T3W6 ;
    conn_list                   _adj4 ;

  //node_maps                   _mmN1 ;
    edge_maps                   _mmE2 ;
    tri3_maps                   _mmT3 ;
    quad_maps                   _mmQ4 ;
    tri4_maps                   _mmT4 ;    
    hexa_maps                   _mmH8 ;
    pyra_maps                   _mmP5 ;
    wedg_maps                   _mmW6 ;

    node_list                   _llN1 ;
    edge_list                   _llE2 ;
    tri3_list                   _llT3 ;
    quad_list                   _llQ4 ;
    tri4_list                   _llT4 ;
    hexa_list                   _llH8 ;
    pyra_list                   _llP5 ;
    wedg_list                   _llW6 ;

    iptr_list                   _del1 ;
    iptr_list                   _del2 ;
    iptr_list                   _del3 ;
    iptr_list                   _del4 ;
    
    iptr_list                   _tmp1 ;
    iptr_list                   _tmp2 ;
    iptr_list                   _tmp3 ;
    iptr_list                   _tmp4 ;

    public  :

    /*
    --------------------------------------------------------
     * GET-NODE: "create" new node, push onto active set.
    --------------------------------------------------------
     */
     
    __inline_call iptr_type _get_node (
        )
    {
        iptr_type _ipos = -1;
        if (this->_del1.count() != +0 )
        {
    /*---------------------------- recycle from free list */
            this->_del1._pop_tail(_ipos) ;
        }
        else
        {
    /*---------------------------- alloc. from underlying */
            _ipos = (iptr_type)
                this->_set1.count() ;
            this->_set1.push_tail() ;
        }

        this->_set1[_ipos].mark() = +0 ;
        this->_set1[_ipos].self() = +0 ;
        
        return ( _ipos ) ;
    }
    
    /*
    --------------------------------------------------------
     * GET-EDGE: "create" new edge, push onto active set.
    --------------------------------------------------------
     */
     
    __inline_call iptr_type _get_edge (
        )
    {
        iptr_type _ipos = -1;
        if (this->_del2.count() != +0 )
        {
    /*---------------------------- recycle from free list */
            this->_del2._pop_tail(_ipos) ;
        }
        else
        {
    /*---------------------------- alloc. from underlying */
            _ipos = (iptr_type)
                this->_set2.count() ;
            this->_set2.push_tail() ;
        }

        this->_set2[_ipos].mark() = +0 ;
        this->_set2[_ipos].self() = +0 ;

        return ( _ipos ) ;
    }

    /*
    --------------------------------------------------------
     * GET-TRIA: "create" new tria, push onto active set.
    --------------------------------------------------------
     */
     
    __inline_call iptr_type _get_tri3 (
        )
    {
        iptr_type _ipos = -1;
        if (this->_del3.count() != +0 )
        {
    /*---------------------------- recycle from free list */
            this->_del3._pop_tail(_ipos) ;
        }
        else
        {
    /*---------------------------- alloc. from underlying */
            _ipos = (iptr_type)
                this->_set3.count() ;
            this->_set3.push_tail() ;
        }

        this->_set3[_ipos].mark() = +0 ;
        this->_set3[_ipos].self() = +0 ;

        return ( _ipos ) ;
    }
    
    /*
    --------------------------------------------------------
     * GET-TRIA: "create" new tria, push onto active set.
    --------------------------------------------------------
     */
     
    __inline_call iptr_type _get_tri4 (
        )
    {
        iptr_type _ipos = -1;
        if (this->_del4.count() != +0 )
        {
    /*---------------------------- recycle from free list */
            this->_del4._pop_tail(_ipos) ;
        }
        else
        {
    /*---------------------------- alloc. from underlying */
            _ipos = (iptr_type)
                this->_set4.count() ;
            this->_set4.push_tail() ;
        }

        this->_set4[_ipos].mark() = +0 ;
        this->_set4[_ipos].self() = +0 ;

        return ( _ipos ) ;
    }
    
    /*
    --------------------------------------------------------
     * PUT-ITEM: "delete" old item, _pop from active set.
    --------------------------------------------------------
     */
     
    __inline_call void_type _put_node (
        iptr_type _ipos
        )
    {
        this->_del1.push_tail (_ipos);
        this->_set1[_ipos].mark() = -1 ;
        this->_set1[_ipos].self() = -1 ;
    }
    
    __inline_call void_type _put_edge (
        iptr_type _ipos
        )
    {
        this->_del2.push_tail (_ipos);
        this->_set2[_ipos].mark() = -1 ;
        this->_set2[_ipos].self() = -1 ;
    }
    
    __inline_call void_type _put_tri3 (
        iptr_type _ipos
        )
    {
        this->_del3.push_tail (_ipos);
        this->_set3[_ipos].mark() = -1 ;
        this->_set3[_ipos].self() = -1 ;
    }
    
    __inline_call void_type _put_tri4 (
        iptr_type _ipos
        )
    {
        this->_del4.push_tail (_ipos);
        this->_set4[_ipos].mark() = -1 ;
        this->_set4[_ipos].self() = -1 ;
    }
    
    public  :
    
    /*
    --------------------------------------------------------
     * construct tria_complex from alloc. etc...
    --------------------------------------------------------
     */
     
    __normal_call tria_complex_3 (
        allocator const& _asrc = allocator()
        ) : _hsrc(sizeof (
            typename tri4_maps::item_type)),
            _csrc(sizeof (
            typename conn_list::item_type)),
        /*------------------------------ init. adj. lists */
            _adj1(pool_wrap(&_csrc)),
            _adj2(pool_wrap(&_csrc)),
            _adj3(pool_wrap(&_csrc)),
            _adj4(pool_wrap(&_csrc)),
        /*------------------------------ init. hash lists */
          //_map1(
          // node_hash(& this->_set1) , 
          // node_pred(& this->_set1) , 
          //+.8, (pool_wrap(&_hsrc))) ,
            _map2(
             edge_hash(& this->_set2) , 
             edge_pred(& this->_set2) , 
            +.8, (pool_wrap(&_hsrc))) ,
            _map3(
             tri3_hash(& this->_set3) , 
             tri3_pred(& this->_set3) , 
            +.8, (pool_wrap(&_hsrc))) ,
            _map4(
             tri4_hash(& this->_set4) , 
             tri4_pred(& this->_set4) , 
            +.8, (pool_wrap(&_hsrc))) ,
        /*------------------------------ init. face lists */
            _set1(_asrc),_set2(_asrc) ,
            _set3(_asrc),_set4(_asrc) ,
        /*------------------------------ init. free lists */
            _del1(_asrc),_del2(_asrc) ,
            _del3(_asrc),_del4(_asrc) ,
        /*------------------------------ init. work lists */
            _tmp1(_asrc),_tmp2(_asrc) ,
            _tmp3(_asrc),_tmp4(_asrc)
        {
        }
        
    /*
    --------------------------------------------------------
     * 'clear' a tria-complex
    --------------------------------------------------------
     */
        
    __normal_call void_type clear (
        containers::alloc_types _kind = 
        containers::loose_alloc
        )
    {
            this->_adj1.clear (_kind) ;
            this->_adj2.clear (_kind) ;
            this->_adj3.clear (_kind) ;
            this->_adj4.clear (_kind) ;
            
          //this->_map1.clear (_kind) ;
            this->_map2.clear (_kind) ;
            this->_map3.clear (_kind) ;
            this->_map4.clear (_kind) ;

            this->_set1.clear (_kind) ;
            this->_set2.clear (_kind) ;
            this->_set3.clear (_kind) ;
            this->_set4.clear (_kind) ;
       
            this->_del1.clear (_kind) ;
            this->_del2.clear (_kind) ;
            this->_del3.clear (_kind) ;
            this->_del4.clear (_kind) ;
        
            this->_tmp1.clear (_kind) ;
            this->_tmp2.clear (_kind) ;
            this->_tmp3.clear (_kind) ;
            this->_tmp4.clear (_kind) ;
            
            this->_hsrc.clear ();
            this->_csrc.clear ();
    }
    
    /*
    --------------------------------------------------------
     * INIT-LIST: re-size adj. lists on demand.
    --------------------------------------------------------
     */
     
    __inline_call void_type init_list (
        conn_list&_list,
        size_type _lpos
        )
    {
        if (_lpos >= _list._lptr.count())
        _list._lptr.set_count (
            _lpos + 1, 
        containers::loose_alloc, nullptr) ;
    }
    
    /*
    --------------------------------------------------------
     * PUSH-NODE: append new 0-node to complex.
    --------------------------------------------------------
     */
     
    __normal_call iptr_type push_node (
        node_type const& _ndat,
        bool_type _link = true,
        iptr_type _itop = -1
        )
    {
        iptr_type _ipos = -1 ;
        
        if (!_link)
        {
        
        __assert( _itop == -1 &&
        "tria-complex: non-top node!" ) ;

    /*------------------------ init. external d-face data */
       _ipos = _get_node();        

        this->_set1[_ipos]  = _ndat ;
        this->_set1[_ipos].mark() = 0 ;
        
        this->_set1[_ipos].self() = 1 ;
        this->
       _set1 [_ipos].node(0) =_ipos ;
       
    /*------------------------ init. local adj. index set */
        init_list(this->_adj1, _ipos) ;
        
        }
        else
        {
        
        if (_itop == -1)
        {
    /*------------------------ init. external d-face data */
       _ipos = _get_node();        

        this->_set1[_ipos]  = _ndat ;
        this->_set1[_ipos].mark() = 0 ;
        this->_set1[_ipos].self() = 1 ;

        this->
       _set1 [_ipos].node(0) = _ipos;

    /*------------------------ init. local adj. index set */
        init_list(this->_adj1, _ipos) ;
        
        }
        else
        {
    /*------------------------ init. internal d-face data */
        __assert(find_node(
               &_ndat.node(0), _ipos) &&
        "tria-complex: node not here" );

    /*------------------------ append index to adj. lists */   
        this->_adj1.push(
                _itop, _ndat.node(0)) ;
        
        }

        }
        
        return _ipos ;
    }
    
    /*
    --------------------------------------------------------
     * PUSH-EDGE: append new 1-edge to complex.
    --------------------------------------------------------
     */
     
    __normal_call iptr_type push_edge (
        edge_type const& _edat,
        bool_type _link = true,
        iptr_type _itop = -1   
        )
    {
        iptr_type _ipos = _get_edge() ;
        iptr_type _npos ;
        
        if (!_link)
        {
            
        __assert( _itop == -1 &&
        "tria-complex: non-top cell!" ) ;

    /*------------------------ init. external d-face data */
        this->_set2[_ipos]  = _edat ;
        this->_set2[_ipos].mark() = 0 ;
        this->_set2[_ipos].self() = 1 ;
        
    /*------------------------ init. local adj. index set */
        init_list(this->_adj2, _ipos) ;
        
        }
        else
        {
        
    /*------------------------ init. external d-face data */
        this->_set2[_ipos]  = _edat ;
        this->_set2[_ipos].mark() = 0 ;
        
        if (_itop == -1)
        this->_set2[_ipos].self() = 1 ;
        else
        this->_set2[_ipos].self() = 0 ;
    
        typename
        edge_maps::_write_it  _same ;
        if (this->
           _map2.find(_ipos , _same))
        {
    /*---- existing d-face found: append to existing data */
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, copy data */
                this->_set2[*_same] =
                this->_set2[ _ipos] ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj2.push(_itop,*_same) ;
            }      
                     
            _put_edge(_ipos) ; 
        }
        else
        {
    /*---- d-face is new: push and descend to (d-1)-faces */   
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, keep data */
                init_list(
                    this->_adj2, _ipos) ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj2.push(_itop, _ipos) ;
            }
            
        /*-------------- descend into (d-1)-face data */
            for (_npos = 2; _npos-- != 0; )
            {
                node_type _ndat;                
                _ndat.node(0) = 
                    _edat.node(_npos) ;
                
                push_node(
                 _ndat, _link, _ipos) ;
            }
            
        /*-------------- push new face data onto hash */
            this->_map2.push(_ipos) ;
        }
        
        }
        
        return _ipos ;
    }
    
    /*
    --------------------------------------------------------
     * PUSH-TRIA: append new 2-tria to complex.
    --------------------------------------------------------
     */
     
    __normal_call iptr_type push_tri3 (
        tri3_type const& _tdat,
        bool_type _link = true,
        iptr_type _itop = -1   
        )
    {
        iptr_type _ipos = _get_tri3() ;
        iptr_type _epos ;
    
        if (!_link)
        {
        
        __assert( _itop == -1 &&
        "tria-complex: non-top cell!" ) ;

    /*-------------------- init. external d-face data */
        this->_set3[_ipos]  = _tdat ;
        this->_set3[_ipos].mark() = 0 ;
        this->_set3[_ipos].self() = 1 ;
        
    /*-------------------- init. local adj. index set */
        init_list(this->_adj3, _ipos) ;
        
        }
        else
        {
    
    /*------------------------ init. external d-face data */
        this->_set3[_ipos]  = _tdat ;
        this->_set3[_ipos].mark() = 0 ;
        
        if (_itop == -1)
        this->_set3[_ipos].self() = 1 ;
        else
        this->_set3[_ipos].self() = 0 ;
    
        typename
        tri3_maps::_write_it  _same ;
        if (this->
           _map3.find(_ipos , _same))
        {
    /*---- existing d-face found: append to existing data */
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, copy data */
                this->_set3[*_same] =
                this->_set3[ _ipos] ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj3.push(_itop,*_same) ;
            }      
                     
            _put_tri3(_ipos) ; 
        }
        else
        {
    /*---- d-face is new: push and descend to (d-1)-faces */   
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, keep data */
                init_list(
                    this->_adj3, _ipos) ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj3.push(_itop, _ipos) ;
            }
            
        /*-------------- descend into (d-1)-face data */
            for (_epos = +3; _epos-- != 0 ; )
            {
                iptr_type  _enod [3];
                tri3_type::face_node(
                    _enod, _epos, 2, 1) ;
                
                edge_type _edat ;
                _edat.node(0) = 
                    _tdat.node(_enod[0]) ;
                _edat.node(1) = 
                    _tdat.node(_enod[1]) ;
                
                push_edge(
                    _edat, _link, _ipos) ;
            }
            
        /*-------------- push new face data onto hash */
            this->_map3.push(_ipos) ;
        }
        
        }
        
        return _ipos ;
    }
    
    /*
    --------------------------------------------------------
     * PUSH-TRIA: append new 3-tria to complex.
    --------------------------------------------------------
     */
     
    __normal_call iptr_type push_tri4 (
        tri4_type const& _tdat,
        bool_type _link = true,
        iptr_type _itop = -1   
        )
    {
        iptr_type _ipos = _get_tri4() ;
        iptr_type _fpos ;
        
        if (!_link)
        {
        
        __assert( _itop == -1 &&
        "tria-complex: non-top cell!" ) ;

    /*------------------------ init. external d-face data */
        this->_set4[_ipos]  = _tdat ;
        this->_set4[_ipos].mark() = 0 ;
        this->_set4[_ipos].self() = 1 ;
        
    /*------------------------ init. local adj. index set */
        init_list(this->_adj4, _ipos) ;
        
        }
        else
        {
    
    /*------------------------ init. external d-face data */
        this->_set4[_ipos]  = _tdat ;
        this->_set4[_ipos].mark() = 0 ;
        
        if (_itop == -1)
        this->_set4[_ipos].self() = 1 ;
        else
        this->_set4[_ipos].self() = 0 ;
    
        typename
        tri4_maps::_write_it  _same ;
        if (this->
           _map4.find(_ipos , _same))
        {
    /*---- existing d-face found: append to existing data */
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, copy data */
                this->_set4[*_same] =
                this->_set4[ _ipos] ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj4.push(_itop,*_same) ;
            }    
                       
            _put_tri4(_ipos) ; 
        }
        else
        {
    /*---- d-face is new: push and descend to (d-1)-faces */   
            if (_itop == -1)
            {
        /*----- if it's a "top"-level face, keep data */
                init_list(
                    this->_adj4, _ipos) ;
            }
            else
            {
        /*----- otherwise, append index to adj. lists */
                this->
               _adj4.push(_itop, _ipos) ;
            }
            
        /*-------------- descend into (d-1)-face data */
            for (_fpos = +4; _fpos-- != 0 ; )
            {
                iptr_type  _fnod [4];
                tri4_type::face_node(
                    _fnod, _fpos, 3, 2) ;
                
                tri3_type _fdat ;
                _fdat.node(0) = 
                    _tdat.node(_fnod[0]) ;
                _fdat.node(1) = 
                    _tdat.node(_fnod[1]) ;
                _fdat.node(2) = 
                    _tdat.node(_fnod[2]) ;
                
                push_tri3(
                    _fdat, _link, _ipos) ;
            }
            
        /*-------------- push new face data onto hash */
            this->_map4.push(_ipos) ;
        }
        
        }
        
        return _ipos ;
    }

    /*
    --------------------------------------------------------
     * MAKE-LINK: build item-to-item adj.
    --------------------------------------------------------
     */
  
    __normal_call void_type make_link (
        )
    {
        this->_map2.set_slots(
            (this->_set2.count()*5)/4 + 1
          + (this->_set3.count()*5)/2 + 1
          + (this->_set4.count()*3)/2 + 1 
            ) ;

        this->_map3.set_slots(
            (this->_set3.count()*5)/4 + 1
          + (this->_set4.count()*5)/2 + 1 
            ) ;

        this->_map4.set_slots(
            (this->_set4.count()*5)/4 + 1 
            ) ;

        this->_adj1.empty () ;
        this->_adj2.empty () ;
        this->_adj3.empty () ;
        this->_adj4.empty () ;
    
        iptr_type _epos = +0 ;
        for (auto _iter  = this->_set2.head();
                  _iter != this->_set2.tend();
                ++_iter, ++_epos  )
        {
        /*-------------- push face data onto hash set */
            this->_map2.push(_epos) ;

        /*-------------- descend into (d-1)-face data */
            iptr_type _ipos;
            for (_ipos = +2; _ipos-- != 0; )
            {
                node_type _ndat;                
                _ndat.node(0) = 
                    _iter->node( _ipos) ;
                
                push_node(
                    _ndat, true, _epos) ;
            }
        }
        
        iptr_type _fpos = +0 ;
        for (auto _iter  = this->_set3.head();
                  _iter != this->_set3.tend();
                ++_iter, ++_fpos  )
        {
        /*-------------- push face data onto hash set */
            this->_map3.push(_fpos) ;

        /*-------------- descend into (d-1)-face data */
            iptr_type _ipos;
            for (_ipos = +3; _ipos-- != 0; )
            {
                iptr_type  _enod [3];
                tri3_type::face_node(
                    _enod, _ipos, 2, 1 ) ;
                
                edge_type  _edat ;
                _edat.node(0) = 
                   _iter->node(_enod[0]) ;
                _edat.node(1) = 
                   _iter->node(_enod[1]) ;
                
                push_edge(
                    _edat, true , _fpos) ;
            }
        }
        
        iptr_type _tpos = +0 ;
        for (auto _iter  = this->_set4.head();
                  _iter != this->_set4.tend();
                ++_iter, ++_tpos  )
        {
        /*-------------- push face data onto hash set */
            this->_map4.push(_tpos) ;

        /*-------------- descend into (d-1)-face data */
            iptr_type _ipos;
            for (_ipos = +4; _ipos-- != 0; )
            {
                iptr_type  _fnod [4];
                tri4_type::face_node(
                    _fnod, _ipos, 3, 2 ) ;
                
                tri3_type _fdat ;
                _fdat.node(0) = 
                   _iter->node(_fnod[0]) ;
                _fdat.node(1) = 
                   _iter->node(_fnod[1]) ;
                _fdat.node(2) = 
                   _iter->node(_fnod[2]) ;
                
                push_tri3(
                    _fdat, true , _tpos) ;
            }
        }
    }
  
    /*
    --------------------------------------------------------
     * NULL-ITEM: TRUE if item is delete-able.
    --------------------------------------------------------
     */
     
    __inline_call bool_type null_node (
        iptr_type _npos
        ) const
    {
        return this->_set1[_npos].self()==0
            && this->_adj1.empty(_npos);
    }
    
    __inline_call bool_type null_edge (
        iptr_type _epos
        ) const
    {
        return this->_set2[_epos].self()==0
            && this->_adj2.empty(_epos);
    }
  
    __inline_call bool_type null_tri3 (
        iptr_type _tpos
        ) const
    {
        return this->_set3[_tpos].self()==0
            && this->_adj3.empty(_tpos);
    }
    
    __inline_call bool_type null_tri4 (
        iptr_type _tpos
        ) const
    {
        return this->_set4[_tpos].self()==0
            && this->_adj4.empty(_tpos);
    }
  
    /*
    --------------------------------------------------------
     * _POP-LIST: delete item from adj. list.
    --------------------------------------------------------
     */
     
    __normal_call void_type _pop_list (
        conn_list &_list,
        iptr_type  _lpos,
        iptr_type  _itop
        )
    {
    /*--------------------------- scan list and pop match */
        typename conn_list::_write_it
           _prev = _list.hend(_lpos),
           _iter = _list.head(_lpos),
           _tend = _list.tend(_lpos);
        
        for ( ; _iter != _tend; 
                _prev  = _iter, ++_iter)
        {
            if(*_iter == _itop)
            {
                _list._pop (
                    _prev, _iter, _lpos) ; 
                
                break  ;
            }
        }
    }
  
    /*
    --------------------------------------------------------
     * _POP-NODE: delete 0-node from complex.
    --------------------------------------------------------
     */
     
    __normal_call void_type _pop_node (
        iptr_type const*_nptr,
        iptr_type _itop = -1
        )
    {
        iptr_type _npos = -1 ;
        
        iptr_type  _node[1];
        _node[0] = _nptr[0];
        
    /*-------------------------- find current 0-node pos. */
        if ( !find_node (_node, _npos))
        {
            return ;
        }
    
    /*-------------------------- _pop current 0-node data */   
        _pop_node(_npos, _itop) ;
    }
    
    __normal_call void_type _pop_node (
        iptr_type _npos ,
        iptr_type _itop
        )
    {
        if (_itop != -1)
        {
    /*---- deleteing (d+k)-face: scan adj. and _pop _itop */
            _pop_list(
            this->_adj1, _npos, _itop);
        }
        else
        {
    /*---- deleting (d+0)-face: set "self" marker to null */
            this->
           _set1[_npos].self() = 0 ;
        }
       
        if (null_node (_npos))
        {
    /*---- ref. count: delete (d+0), (d-1)-faces if empty */
            _put_node (_npos); 
        }
    }
  
    /*
    --------------------------------------------------------
     * _POP-EDGE: delete 1-edge from complex.
    --------------------------------------------------------
     */
     
    __normal_call void_type _pop_edge (
        iptr_type const*_nptr,
        iptr_type _itop = -1
        )
    {
        iptr_type _epos = -1 ;
        
        iptr_type  _node[2];
        _node[0] = _nptr[0];
        _node[1] = _nptr[1];
        
    /*-------------------------- find current 1-edge pos. */
        if ( !find_edge (_node, _epos))
        {
            return ;
        }
        
    /*-------------------------- _pop current 1-edge data */   
        _pop_edge(_epos, _itop) ;
    }
     
    __normal_call void_type _pop_edge (
        iptr_type _epos ,
        iptr_type _itop = -1
        )
    {   
        iptr_type _npos = -1 ;
    
        if (_itop != -1)
        {
    /*---- deleteing (d+k)-face: scan adj. and _pop _itop */
            _pop_list(
            this->_adj2, _epos, _itop);
        }
        else
        {
    /*---- deleting (d+0)-face: set "self" marker to null */
            this->
           _set2[_epos].self() = 0 ;
        }
       
        if (null_edge (_epos))
        {
    /*---- ref. count: delete (d+0), (d-1)-faces if empty */
        iptr_type _same ;
        this->_map2._pop(_epos, _same);
        
        iptr_type _node [ 2] ;
        _node[0] = this->
            _set2[_epos].node(0) ;
        _node[1] = this->
            _set2[_epos].node(1) ;
        
        _put_edge(_epos);
        
        for (_npos = 2; _npos-- != 0; )
        {
            _pop_node(
               &_node[_npos], _epos);
        }
        }
    }
  
    /*
    --------------------------------------------------------
     * _POP-TRIA: delete 2-tria from complex.
    --------------------------------------------------------
     */
     
    __normal_call void_type _pop_tri3 (
        iptr_type const*_nptr,
        iptr_type _itop = -1
        )
    {
        iptr_type _tpos = -1 ;
        
        iptr_type  _node[3];
        _node[0] = _nptr[0];
        _node[1] = _nptr[1];
        _node[2] = _nptr[2];
        
    /*-------------------------- find current 2-tria pos. */
        if ( !find_tri3 (_node, _tpos))
        {
            return ;
        }
 
    /*-------------------------- _pop current 2-tria data */   
        _pop_tri3(_tpos, _itop) ;
    }
    
    __normal_call void_type _pop_tri3 (
        iptr_type _tpos ,
        iptr_type _itop = -1
        )
    {   
        iptr_type _epos = -1 ;
    
        if (_itop != -1)
        {
    /*---- deleteing (d+k)-face: scan adj. and _pop _itop */
            _pop_list(
            this->_adj3, _tpos, _itop);
        }
        else
        {
    /*---- deleting (d+0)-face: set "self" marker to null */
            this->
           _set3[_tpos].self() = 0 ;
        }
       
        if (null_tri3 (_tpos))
        {
    /*---- ref. count: delete (d+0), (d-1)-faces if empty */
        
        iptr_type _same ;
        this->_map3._pop(_tpos, _same);
        
        iptr_type _node [ 3] ;
        _node[0] = this->
            _set3[_tpos].node(0) ;
        _node[1] = this->
            _set3[_tpos].node(1) ;
        _node[2] = this->
            _set3[_tpos].node(2) ;
        
        _put_tri3(_tpos);
        
        for (_epos = 3; _epos-- != 0; )
        {
            iptr_type  _enod [3] ;
            tri3_type::face_node (
                _enod, _epos, 2, 1) ;
            
            _enod[0] = 
                _node[_enod [0]];
            _enod[1] = 
                _node[_enod [1]];
            
            _pop_edge(_enod, _tpos) ;
        }
        }
    }
    
    /*
    --------------------------------------------------------
     * _POP-TRIA: delete 3-tria from complex.
    --------------------------------------------------------
     */
     
    __normal_call void_type _pop_tri4 (
        iptr_type const*_nptr,
        iptr_type _itop = -1
        )
    {
        iptr_type _tpos = -1 ;
        
        iptr_type  _node[4];
        _node[0] = _nptr[0];
        _node[1] = _nptr[1];
        _node[2] = _nptr[2];
        _node[3] = _nptr[3];
        
    /*-------------------------- find current 3-tria pos. */
        if ( !find_tri4 (_node, _tpos))
        {
            return ;
        }
 
    /*-------------------------- _pop current 3-tria data */   
        _pop_tri4(_tpos, _itop) ;
    }
    
    __normal_call void_type _pop_tri4 (
        iptr_type _tpos ,
        iptr_type _itop = -1
        )
    {   
        iptr_type _fpos = -1 ;
    
        if (_itop != -1)
        {
    /*---- deleteing (d+k)-face: scan adj. and _pop _itop */
            _pop_list(
            this->_adj4, _tpos, _itop);
        }
        else
        {
    /*---- deleting (d+0)-face: set "self" marker to null */
            this->
           _set4[_tpos].self() = 0 ;
        }
       
        if (null_tri4 (_tpos))
        {
    /*---- ref. count: delete (d+0), (d-1)-faces if empty */
        
        iptr_type _same ;
        this->_map4._pop(_tpos, _same);
        
        iptr_type _node [ 4] ;
        _node[0] = this->
            _set4[_tpos].node(0) ;
        _node[1] = this->
            _set4[_tpos].node(1) ;
        _node[2] = this->
            _set4[_tpos].node(2) ;
        _node[3] = this->
            _set4[_tpos].node(3) ;
        
        _put_tri4(_tpos);
        
        for (_fpos = 4; _fpos-- != 0; )
        {
            iptr_type  _fnod [4] ;
            tri4_type::face_node (
                _fnod, _fpos, 3, 2) ;
            
            _fnod[0] = 
                _node[_fnod [0]];
            _fnod[1] = 
                _node[_fnod [1]];
            _fnod[2] = 
                _node[_fnod [2]];
            
            _pop_tri3(_fnod, _tpos) ;
        }
        }
    }
     
    /*
    --------------------------------------------------------
     * FIND-NODE: return index of assoc. 0-node.
    --------------------------------------------------------
     */
     
    __normal_call bool_type find_node (
        iptr_type const*_nptr ,
        iptr_type&_npos
        ) const
    {
    /*-------------------------- find current 0-node pos. */
        iptr_type _node = *_nptr ;
        
        if (_node >= +0 && _node < 
            (iptr_type)this->_set1.count() &&
            _set1 [_node].mark() >= +0)
        {
    /*------------------------------- found matching node */
            _npos =_node ;
        
            return  true ;
        }
        else
        {
    /*------------------------------- couldn't find match */
            return false ;
        }
    }

    /*
    --------------------------------------------------------
     * FIND-EDGE: return index of assoc. 1-edge.
    --------------------------------------------------------
     */
     
    __normal_call bool_type find_edge (
        iptr_type const*_node ,
        iptr_type&_epos
        )
    {
    /*-------------------------- find current 1-edge pos. */
        iptr_type _ipos = _get_edge() ;
        
        this->
       _set2[_ipos].node(0)=_node[0];
        this->
       _set2[_ipos].node(1)=_node[1];      
        
        typename edge_maps::_write_it 
           _same ;
        if (this->
           _map2.find(_ipos, _same))
        {
    /*------------------------------- found matching face */
            _put_edge(_ipos) ;

            _epos=*_same ;
        
            return  true ;
        }
        else
        {
    /*------------------------------- couldn't find match */
            _put_edge(_ipos) ;

            return false ;
        }
    }
    
    /*
    --------------------------------------------------------
     * FIND-TRIA: return index of assoc. 2-tria.
    --------------------------------------------------------
     */
     
    __normal_call bool_type find_tri3 (
        iptr_type const*_node ,
        iptr_type&_tpos
        )
    {
    /*-------------------------- find current 2-tria pos. */        
        iptr_type _ipos = _get_tri3() ;
        
        this->
       _set3[_ipos].node(0)=_node[0];
        this->
       _set3[_ipos].node(1)=_node[1];
        this->
       _set3[_ipos].node(2)=_node[2];      
        
        typename tri3_maps::_write_it 
           _same ;
        if (this->
           _map3.find(_ipos, _same))
        {
    /*------------------------------- found matching face */
            _put_tri3(_ipos) ;

            _tpos=*_same ;
        
            return  true ;
        }
        else
        {
    /*------------------------------- couldn't find match */
            _put_tri3(_ipos) ;

            return false ;
        }
    }
    
    /*
    --------------------------------------------------------
     * FIND-TRIA: return index of assoc. 3-tria.
    --------------------------------------------------------
     */
     
    __normal_call bool_type find_tri4 (
        iptr_type const*_node ,
        iptr_type&_tpos
        )
    {
    /*-------------------------- find current 2-tria pos. */        
        iptr_type _ipos = _get_tri4() ;
        
        this->
       _set4[_ipos].node(0)=_node[0];
        this->
       _set4[_ipos].node(1)=_node[1];
        this->
       _set4[_ipos].node(2)=_node[2];
        this->
       _set4[_ipos].node(3)=_node[3];      
        
        typename tri4_maps::_write_it 
           _same ;
        if (this->
           _map4.find(_ipos, _same))
        {
    /*------------------------------- found matching face */
            _put_tri4(_ipos) ;

            _tpos=*_same ;
        
            return  true ;
        }
        else
        {
    /*------------------------------- couldn't find match */
            _put_tri4(_ipos) ;

            return false ;
        }
    }
    
    
    /*
    --------------------------------------------------------
     * NODE-EDGE: form node-to-edge adj. list.
    --------------------------------------------------------
     */
     
    template <
    typename      list_type
             >
    __inline_call void_type node_edge (
        iptr_type const*_node ,
        list_type&_conn
        )
    {
        node_edge(_node [ 0], _conn) ;
    }     
        
    template <
    typename      list_type
             >
    __normal_call void_type node_edge (
        iptr_type _npos,
        list_type&_conn
        )
    {   
        this->_tmp1.set_count(  +0 ) ;
        this->_tmp2.set_count(  +0 ) ;
        this->_tmp3.set_count(  +0 ) ;
        this->_tmp4.set_count(  +0 ) ;
      
        this->_tmp1.push_tail(_npos) ;
       
    /*-------------------------- find set of adj. 1-edges */
        for (auto _iter  = this->_tmp1.head(); 
                  _iter != this->_tmp1.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj1.head(*_iter) ;
                      _iadj != 
                 this->_adj1.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set2[*_iadj].mark() == 0)
                {
                   _conn.push_tail (*_iadj);
                    this->
                   _set2[*_iadj].mark() += 1;
                }
            }
        }
  
    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
            this->_set2 [*_iter].mark() = +0;
        }
    }
    
    /*
    --------------------------------------------------------
     * NODE-TRI3: form node-to-tria adj. list.
    --------------------------------------------------------
     */
     
    template <
    typename      list_type
             >
    __inline_call void_type node_tri3 (
        iptr_type const*_node ,
        list_type&_conn
        )
    {
        node_tri3(_node [ 0], _conn) ;
    }
   
    template <
    typename      list_type
             >
    __normal_call void_type node_tri3 (
        iptr_type _npos,
        list_type&_conn
        )
    {   
        this->_tmp1.set_count(  +0 ) ;
        this->_tmp2.set_count(  +0 ) ;
        this->_tmp3.set_count(  +0 ) ;
        this->_tmp4.set_count(  +0 ) ;
       
        this->_tmp1.push_tail(_npos) ;
       
    /*-------------------------- find set of adj. 1-edges */
        for (auto _iter  = this->_tmp1.head(); 
                  _iter != this->_tmp1.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj1.head(*_iter) ;
                      _iadj != 
                 this->_adj1.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set2[*_iadj].mark() == 0)
                {
                    this->
                   _tmp2.push_tail (*_iadj);
                    this->
                   _set2[*_iadj].mark() += 1;
                }
            }
        }
    /*-------------------------- find set of adj. 2-trias */
        for (auto _iter  = this->_tmp2.head(); 
                  _iter != this->_tmp2.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj2.head(*_iter) ;
                      _iadj != 
                 this->_adj2.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set3[*_iadj].mark() == 0)
                {
                   _conn.push_tail (*_iadj);
                    this->
                   _set3[*_iadj].mark() += 1;
                }
            }
        }
  
    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
            this->_set3 [*_iter].mark() = 0 ;
        }
        for (auto _iter  =  this->
                           _tmp2.head() ; 
                  _iter !=  this->
                           _tmp2.tend() ;
                ++_iter  )
        {
            this->_set2 [*_iter].mark() = 0 ;
        }
    }
    
    /*
    --------------------------------------------------------
     * NODE-TRI4: form node-to-tria adj. list.
    --------------------------------------------------------
     */
    
    template <
    typename      list_type
             >
    __inline_call void_type node_tri4 (
        iptr_type const*_node ,
        list_type&_conn
        )
    {
        node_tri4(_node [ 0], _conn) ;
    }
    
    template <
    typename      list_type
             >
    __normal_call void_type node_tri4 (
        iptr_type _npos,
        list_type&_conn
        )
    {   
        this->_tmp1.set_count(  +0 ) ;
        this->_tmp2.set_count(  +0 ) ;
        this->_tmp3.set_count(  +0 ) ;
        this->_tmp4.set_count(  +0 ) ;
       
        this->_tmp1.push_tail(_npos) ;
       
    /*-------------------------- find set of adj. 1-edges */
        for (auto _iter  = this->_tmp1.head(); 
                  _iter != this->_tmp1.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj1.head(*_iter) ;
                      _iadj != 
                 this->_adj1.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set2[*_iadj].mark() == 0)
                {
                    this->
                   _tmp2.push_tail (*_iadj);
                    this->
                   _set2[*_iadj].mark() += 1;
                }
            }
        }
    /*-------------------------- find set of adj. 2-trias */
        for (auto _iter  = this->_tmp2.head(); 
                  _iter != this->_tmp2.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj2.head(*_iter) ;
                      _iadj != 
                 this->_adj2.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set3[*_iadj].mark() == 0)
                {
                    this->
                   _tmp3.push_tail (*_iadj);
                    this->
                   _set3[*_iadj].mark() += 1;
                }
            }
        }
    /*-------------------------- find set of adj. 3-trias */
        for (auto _iter  = this->_tmp3.head(); 
                  _iter != this->_tmp3.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj3.head(*_iter) ;
                      _iadj != 
                 this->_adj3.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set4[*_iadj].mark() == 0)
                {
                   _conn.push_tail (*_iadj);
                    this->
                   _set4[*_iadj].mark() += 1;
                }
            }
        }
  
    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
            this->_set4 [*_iter].mark() = 0 ;
        }
        for (auto _iter  =  this->
                           _tmp3.head() ; 
                  _iter !=  this->
                           _tmp3.tend() ;
                ++_iter  )
        {
            this->_set3 [*_iter].mark() = 0 ;
        }
        for (auto _iter  =  this->
                           _tmp2.head() ; 
                  _iter !=  this->
                           _tmp2.tend() ;
                ++_iter  )
        {
            this->_set2 [*_iter].mark() = 0 ;
        }
    }
       
    /*
    --------------------------------------------------------
     * EDGE-TRI3: form edge-to-tria adj. list.
    --------------------------------------------------------
     */
     
    template <
    typename      list_type
             >
    __inline_call void_type edge_tri3 (
        iptr_type const*_node ,
        list_type&_conn
        )
    {
    /*-------------------------- find current 1-edge pos. */        
        iptr_type _epos = -1;
        if (!find_edge(_node, _epos))
        {
            return ;
        }
        
    /*-------------------------- get adj. for 1-edge pos. */
        edge_tri3(_epos, _conn) ;
    }
   
    template <
    typename      list_type
             >
    __normal_call void_type edge_tri3 (
        iptr_type _epos,
        list_type&_conn
        )
    {
        this->_tmp1.set_count(  +0 ) ;
        this->_tmp2.set_count(  +0 ) ;
        this->_tmp3.set_count(  +0 ) ;
        this->_tmp4.set_count(  +0 ) ;
        
        this->_tmp2.push_tail(_epos) ;
       
    /*-------------------------- find set of adj. 2-faces */
        for (auto _iter  = this->_tmp2.head(); 
                  _iter != this->_tmp2.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj2.head(*_iter) ;
                      _iadj != 
                 this->_adj2.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set3[*_iadj].mark() == 0)
                {
                   _conn.push_tail (*_iadj);
                    this->
                   _set3[*_iadj].mark() += 1;
                }
            }
        }
  
    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
            this->_set3 [*_iter].mark() = 0 ;
        }
    }
    
    /*
    --------------------------------------------------------
     * EDGE-3CEL: form edge-to-cell adj. list.
    --------------------------------------------------------
     */

    __inline_call void_type edge_cell (
        iptr_type const*_node ,
        char_type _kind ,
        connector&_conn
        )
    {
    /*-------------------------- find current 1-edge pos. */        
        iptr_type _epos = -1;
        if (!find_edge(_node, _epos))
        {
            return ;
        }
        
    /*-------------------------- get adj. for 1-edge pos. */
        edge_cell(_epos, _kind, _conn) ;
    }
   
    __normal_call void_type edge_cell (
        iptr_type _epos,
        char_type _kind,
        connector&_conn
        )
    {
        this->_ttN1.set_count(  +0 ) ;
        this->_ttE2.set_count(  +0 ) ;
        this->_ttT3.set_count(  +0 ) ;
        this->_ttQ4.set_count(  +0 ) ;
        this->_ttT4.set_count(  +0 ) ;
        this->_ttH8.set_count(  +0 ) ;        
        this->_ttP5.set_count(  +0 ) ;
        this->_ttW6.set_count(  +0 ) ;

        this->_ttE2.push_tail(_epos) ;
       
    /*-------------------------- find set of adj. 2-faces */
        for (auto _iter  = this->_ttE2.head(); 
                  _iter != this->_ttE2.tend();
                ++_iter  )
        {
            for (auto _iadj  =                  // tria-3
                 this->_E2T3.head(*_iter) ;
                      _iadj != 
                 this->_E2T3.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _llT3[*_iadj].mark() == 0)
                {
                    this->
                   _ttT3.push_tail (*_iadj);
                    this->
                   _llT3[*_iadj].mark() += 1;
                }
            }
            for (auto _iadj  =                  // quad-4
                 this->_E2Q4.head(*_iter) ;
                      _iadj != 
                 this->_E2Q4.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _llQ4[*_iadj].mark() == 0)
                {
                    this->
                   _ttQ4.push_tail (*_iadj);
                    this->
                   _llQ4[*_iadj].mark() += 1;
                }
            }
        }
    /*-------------------------- find set of adj. 3-faces */
        for (auto _iter  = this->_ttT3.head(); 
                  _iter != this->_ttT3.tend();
                ++_iter  )
        {
            for (auto _iadj  =                  // tria-4
                 this->_T3T4.head(*_iter) ;
                      _iadj != 
                 this->_T3T4.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _llT4[*_iadj].mark() == 0)
                {
                   _conn.push_tail(conn_data(
                        *_iadj, tri4_flag));
                    this->
                   _llT4[*_iadj].mark() += 1;
                }
            }
            for (auto _iadj  =                  // pyra-5
                 this->_T3P5.head(*_iter) ;
                      _iadj != 
                 this->_T3P5.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _llP5[*_iadj].mark() == 0)
                {
                   _conn.push_tail(conn_data(
                        *_iadj, pyra_flag));
                    this->
                   _llP5[*_iadj].mark() += 1;
                }
            }
            for (auto _iadj  =                  // wedg-6
                 this->_T3W6.head(*_iter) ;
                      _iadj != 
                 this->_T3W6.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _llW6[*_iadj].mark() == 0)
                {
                   _conn.push_tail(conn_data(
                        *_iadj, wedg_flag));
                    this->
                   _llW6[*_iadj].mark() += 1;
                }
            }
        }

    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
        if (_iter->_flag == tri4_flag)
            _llT4[_iter->_ipos].mark() =  0 ;
        else
        if (_iter->_flag == hexa_flag)
            _llH8[_iter->_ipos].mark() =  0 ;
        else
        if (_iter->_flag == pyra_flag)
            _llP5[_iter->_ipos].mark() =  0 ;
        else
        if (_iter->_flag == wedg_flag)
            _llW6[_iter->_ipos].mark() =  0 ;
        }
        for (auto _iter  =  this->
                           _ttT3.head() ; 
                  _iter !=  this->
                           _ttT3.tend() ;
                ++_iter  )
        {
            this->_llT3 [*_iter].mark() = 0 ;
        }
        for (auto _iter  =  this->
                           _ttQ4.head() ; 
                  _iter !=  this->
                           _ttQ4.tend() ;
                ++_iter  )
        {
            this->_llQ4 [*_iter].mark() = 0 ;
        }
    }
    
    /*
    --------------------------------------------------------
     * TRI3-TRI4: form tria-to-tria adj. list.
    --------------------------------------------------------
     */
     
    template <
    typename      list_type
             >
    __inline_call void_type tri3_tri4 (
        iptr_type const*_node ,
        list_type&_conn
        )
    {
    /*-------------------------- find current 1-edge pos. */        
        iptr_type _tpos = -1;
        if (!find_tri3(_node, _tpos))
        {
            return ;
        }
        
    /*-------------------------- get adj. for 1-edge pos. */
        tri3_tri4(_tpos, _conn) ;
    }
   
    template <
    typename      list_type
             >
    __normal_call void_type tri3_tri4 (
        iptr_type _epos,
        list_type&_conn
        )
    {
        this->_tmp1.set_count(  +0 ) ;
        this->_tmp2.set_count(  +0 ) ;
        this->_tmp3.set_count(  +0 ) ;
        this->_tmp4.set_count(  +0 ) ;
        
        this->_tmp3.push_tail(_epos) ;
       
    /*-------------------------- find set of adj. 2-faces */
        for (auto _iter  = this->_tmp3.head(); 
                  _iter != this->_tmp3.tend();
                ++_iter  )
        {
            for (auto _iadj  = 
                 this->_adj3.head(*_iter) ;
                      _iadj != 
                 this->_adj3.tend(*_iter) ;
                    ++_iadj  )
            {
                if (this->
                   _set4[*_iadj].mark() == 0)
                {
                   _conn.push_tail (*_iadj);
                    this->
                   _set4[*_iadj].mark() += 1;
                }
            }
        }
  
    /*-------------------------- flip d-face marker lists */
        for (auto _iter  = _conn.head() ; 
                  _iter != _conn.tend() ;
                ++_iter  )
        {
            this->_set4 [*_iter].mark() = 0 ;
        }
    }

    } ;


    }

#   endif  // __MESH_COMPLEX_3__



