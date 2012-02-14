/*
   Copyright (C) 2011  Statoil ASA, Norway. 
    
   The file 'enkf_main.h' is part of ERT - Ensemble based Reservoir Tool. 
    
   ERT is free software: you can redistribute it and/or modify 
   it under the terms of the GNU General Public License as published by 
   the Free Software Foundation, either version 3 of the License, or 
   (at your option) any later version. 
    
   ERT is distributed in the hope that it will be useful, but WITHOUT ANY 
   WARRANTY; without even the implied warranty of MERCHANTABILITY or 
   FITNESS FOR A PARTICULAR PURPOSE.   
    
   See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html> 
   for more details. 
*/

#ifndef __ENKF_MAIN_H__
#define __ENKF_MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <enkf_config_node.h>
#include <enkf_types.h>
#include <enkf_state.h>
#include <obs_data.h>
#include <path_fmt.h>
#include <enkf_fs.h>
#include <sched_file.h>
#include <job_queue.h>
#include <util.h>
#include <ext_joblist.h>
#include <stringlist.h>
#include <enkf_obs.h>
#include <forward_model.h>
#include <misfit_table.h>
#include <plot_config.h>
#include <set.h>
#include <member_config.h>
#include <analysis_config.h>
#include <site_config.h>
#include <subst_list.h>
#include <local_config.h>
#include <log.h>  
#include <bool_vector.h>
#include <ert_template.h>
#include <int_vector.h>
#include <matrix.h>

/*****************************************************************/



  typedef struct enkf_main_struct enkf_main_type;
  void                          enkf_main_close_alt_fs(enkf_main_type * enkf_main , enkf_fs_type * fs);
  enkf_fs_type                * enkf_main_get_alt_fs(enkf_main_type * enkf_main , const char * case_path , bool read_only , bool create);
  stringlist_type             * enkf_main_alloc_caselist( const enkf_main_type * enkf_main );
  void                          enkf_main_set_fs( enkf_main_type * enkf_main , enkf_fs_type * fs , const char * case_path );
  char                        * enkf_main_alloc_mount_point( const enkf_main_type * enkf_main , const char * case_path);
  const char                  * enkf_main_get_current_fs( const enkf_main_type * enkf_main );
  void                          enkf_main_user_select_fs(enkf_main_type * enkf_main , const char * case_path );
  void                          enkf_main_set_eclbase( enkf_main_type * enkf_main , const char * eclbase_fmt);
  void                          enkf_main_set_data_file( enkf_main_type * enkf_main , const char * data_file );
  void                          enkf_main_set_user_config_file( enkf_main_type * enkf_main , const char * user_config_file );
  const char                  * enkf_main_get_user_config_file( const enkf_main_type * enkf_main );
  void                          enkf_main_set_rft_config_file( enkf_main_type * enkf_main , const char * rft_config_file );
  const char                  * enkf_main_get_rft_config_file( const enkf_main_type * enkf_main );
  bool                          enkf_main_get_pre_clear_runpath( const enkf_main_type * enkf_main );
  void                          enkf_main_set_pre_clear_runpath( enkf_main_type * enkf_main , bool pre_clear_runpath);
  void                          enkf_main_set_refcase( enkf_main_type * enkf_main , const char * refcase_path);
  
  ert_templates_type          * enkf_main_get_templates( enkf_main_type * enkf_main );
  void                          enkf_main_set_log_file( enkf_main_type * enkf_main , const char * log_file );
  const char                  * enkf_main_get_log_file( const enkf_main_type * enkf_main );
  void                          enkf_main_set_log_level( enkf_main_type * enkf_main , int log_level );
  int                           enkf_main_get_log_level( const enkf_main_type * enkf_main );
  log_type                    * enkf_main_get_logh( const enkf_main_type * enkf_main );
  member_config_type          * enkf_main_iget_member_config(const enkf_main_type * enkf_main , int iens);
  misfit_table_type           * enkf_main_get_misfit(const enkf_main_type * enkf_main);
  void                          enkf_main_del_unused_static(enkf_main_type * , int );
  const char                  * enkf_main_get_data_file(const enkf_main_type * );
  const char                 ** enkf_main_get_well_list_ref(const enkf_main_type * , int *);
  
  bool                          enkf_main_get_endian_swap(const enkf_main_type * );
  bool                          enkf_main_get_fmt_file(const enkf_main_type * );
  bool                          enkf_main_has_key(const enkf_main_type * , const char *);
  void                          enkf_main_add_gen_kw(enkf_main_type * , const char * );
  void                          enkf_main_add_type(enkf_main_type * , const char * , enkf_var_type , ert_impl_type , const char * , const void *);
  void                          enkf_main_add_type0(enkf_main_type * , const char * , int , enkf_var_type , ert_impl_type );
  void                          enkf_main_add_well(enkf_main_type * , const char * , int , const char ** );
  void                          enkf_main_analysis(enkf_main_type * );
  void                          enkf_main_free(enkf_main_type * );
  void                          enkf_main_init_eclipse(enkf_main_type * , int , int );
  void                          enkf_main_init_run( enkf_main_type * enkf_main, run_mode_type run_mode);
  void                          enkf_main_load_ecl_init_mt(enkf_main_type * enkf_main , int );
  void                          enkf_main_load_ecl_complete_mt(enkf_main_type *);
  void                          enkf_main_iload_ecl_mt(enkf_main_type *enkf_main , int );
  bool                          enkf_main_run(enkf_main_type * , run_mode_type , const bool_vector_type * ,  int  , int , state_enum );
  //void                          enkf_main_run_step(enkf_main_type *, run_mode_type , const bool * , int, state_enum , int , int, bool, forward_model_type *);
  void                          enkf_main_set_data_kw(enkf_main_type * , const char * , const char *);
  void                          enkf_main_set_state_run_path(const enkf_main_type * , int );
  void                          enkf_main_set_state_eclbase(const enkf_main_type * , int );
  void                          enkf_main_interactive_set_runpath__(void * );
  enkf_main_type              * enkf_main_bootstrap(const char * , const char * , bool strict, bool verbose);
  void                          enkf_main_create_new_config( const char * config_file , const char * storage_path , const char * case_name , const char * dbase_type , int num_realizations);
  
  enkf_node_type             ** enkf_main_get_node_ensemble(const enkf_main_type * enkf_main , const char * key , int report_step , state_enum load_state);
  void                          enkf_main_node_mean( const enkf_node_type ** ensemble , int ens_size , enkf_node_type * mean );
  void                          enkf_main_node_std( const enkf_node_type ** ensemble , int ens_size , const enkf_node_type * mean , enkf_node_type * std);
  
  ert_impl_type                enkf_main_impl_type(const enkf_main_type *, const char * );
  enkf_state_type             * enkf_main_iget_state(const enkf_main_type * , int );
  enkf_state_type            ** enkf_main_get_ensemble( enkf_main_type * enkf_main);
  
  const enkf_config_node_type * enkf_main_get_config_node(const enkf_main_type * , const char *);
  const sched_file_type       * enkf_main_get_sched_file(const enkf_main_type *);
  ecl_config_type             * enkf_main_get_ecl_config(const enkf_main_type * enkf_main);
  ensemble_config_type        * enkf_main_get_ensemble_config(const enkf_main_type * enkf_main);
  int                           enkf_main_get_ensemble_size( const enkf_main_type * enkf_main );
  int                           enkf_main_get_history_length( const enkf_main_type * );
  bool                          enkf_main_has_prediction( const enkf_main_type *  );
  //const enkf_sched_type       * enkf_main_get_enkf_sched(const enkf_main_type *);
  model_config_type           * enkf_main_get_model_config( const enkf_main_type * );
  local_config_type           * enkf_main_get_local_config( const enkf_main_type * enkf_main );
  plot_config_type            * enkf_main_get_plot_config( const enkf_main_type * enkf_main );
  enkf_fs_type                * enkf_main_get_fs(const enkf_main_type * );
  void                          enkf_main_load_obs( enkf_main_type * enkf_main , const char * obs_config_file );
  void                          enkf_main_reload_obs( enkf_main_type * enkf_main);
  enkf_obs_type               * enkf_main_get_obs(const enkf_main_type * );
  analysis_config_type        * enkf_main_get_analysis_config(const enkf_main_type * );
  void                          enkf_main_select_fs( enkf_main_type * enkf_main , const char * case_path );  

  void       * enkf_main_get_enkf_config_node_type(const ensemble_config_type *, const char *);
  void         enkf_main_set_field_config_iactive(const ensemble_config_type *, int);
  const char * enkf_main_get_image_viewer(const enkf_main_type * );
  const char * enkf_main_get_plot_driver(const enkf_main_type * enkf_main );
  void         enkf_main_analysis_update(enkf_main_type * , int , int );
  const char * enkf_main_get_image_type(const enkf_main_type * enkf_main);
  void         enkf_main_UPDATE(enkf_main_type * enkf_main , const int_vector_type * step_list);
  void         enkf_main_initialize_from_scratch(enkf_main_type * enkf_main , const stringlist_type * param_list , int iens1 , int iens2);
  
  void enkf_main_initialize_from_existing(enkf_main_type * enkf_main , 
                                          const char * source_case , 
                                          int          source_report_step,
                                          state_enum   source_state,
                                          const bool_vector_type * iens_mask,
                                          const char * ranking_key);

  void enkf_main_copy_ensemble(enkf_main_type * enkf_main , 
                               const char * source_case , 
                               int          source_report_step,
                               state_enum   source_state,
                               const char * target_case , 
                               int          target_report_step,
                               state_enum   target_state,
                               const bool_vector_type * iens_mask,
                               const char * ranking_key ,    
                               const stringlist_type * node_list);
  
  void enkf_main_initialize_from_existing__(enkf_main_type * enkf_main , 
                                            const char * source_case , 
                                            int          source_report_step,
                                            state_enum   source_state,
                                            const bool_vector_type * iens_mask,
                                            const char * ranking_key,
                                            const stringlist_type * node_list);
  
  
  const int         * enkf_main_get_ranking_permutation( const enkf_main_type * enkf_main , const char * ranking_key);
  void                enkf_main_set_misfit_table( enkf_main_type * enkf_main , misfit_table_type * misfit);
  misfit_table_type * enkf_main_get_misfit_table( const enkf_main_type * enkf_main );
  void                     enkf_main_set_case_table( enkf_main_type * enkf_main , const char * case_table_file );
  void                     enkf_main_list_users(  set_type * users , const char * executable );
  const ext_joblist_type * enkf_main_get_installed_jobs( const enkf_main_type * enkf_main );
  
  subst_list_type        * enkf_main_get_data_kw( const enkf_main_type * enkf_main );
  void                     enkf_main_clear_data_kw( enkf_main_type * enkf_main );
  site_config_type       * enkf_main_get_site_config( const enkf_main_type * enkf_main );
  void                     enkf_main_resize_ensemble( enkf_main_type * enkf_main , int new_ens_size );
  void                     enkf_main_get_observations( const enkf_main_type * enkf_main, const char * user_key , int obs_count , time_t * obs_time , double * y , double * std);
  int                      enkf_main_get_observation_count( const enkf_main_type * enkf_main, const char * user_key );
  
  keep_runpath_type        enkf_main_iget_keep_runpath( const enkf_main_type * enkf_main , int iens );
  void                     enkf_main_iset_keep_runpath( enkf_main_type * enkf_main , int iens , keep_runpath_type keep_runpath);
  
  /*****************************************************************/
  void                        enkf_main_install_SIGNALS(void);
  const                char * enkf_main_get_SVN_VERSION( void );
  const                char * enkf_main_get_COMPILE_TIME( void );
  void                        enkf_main_init_debug( const char * executable) ;
  bool                        enkf_main_is_initialized( const enkf_main_type * enkf_main ,bool_vector_type * __mask);
  void                        enkf_main_del_node(enkf_main_type * enkf_main , const char * key);
  void                        enkf_main_update_node( enkf_main_type * enkf_main , const char * key );
  void                        enkf_main_fprintf_config( const enkf_main_type * enkf_main );
  int_vector_type           * enkf_main_update_alloc_step_list( const enkf_main_type * enkf_main , int load_start , int step2 );
  
  void enkf_main_get_PC( const enkf_main_type * enkf_main , 
                         const matrix_type * S, 
                         const matrix_type * dObs,
                         const char * obsset_name , 
                         int step1 , int step2 , 
                         double truncation , 
                         int ncomp , 
                         matrix_type * PC , 
                         matrix_type * PC_obs);
  
  
  void                   enkf_main_set_verbose( enkf_main_type * enkf_main , bool verbose);
  bool                   enkf_main_get_verbose( const enkf_main_type * enkf_main );

UTIL_SAFE_CAST_HEADER(enkf_main);

#ifdef __cplusplus
}
#endif
#endif
