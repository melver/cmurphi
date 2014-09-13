/******************************
  Program "/home/melatti/assegnoRoma1/ricerca/CMurphi/refactored/cmurphi5.4.6//ex/sci/scierr.m" compiled by "Caching Murphi Release 5.4.6"

  Murphi Last Compiled date: "Apr 28 2011"
 ******************************/

/********************
  Parameter
 ********************/
#define MURPHI_VERSION "Caching Murphi Release 5.4.6"
#define MURPHI_DATE "Apr 28 2011"
#define PROTOCOL_NAME "/home/melatti/assegnoRoma1/ricerca/CMurphi/refactored/cmurphi5.4.6//ex/sci/scierr"
#define BITS_IN_WORLD 277
#define HASHC
#define CACHED_MURPHI

/********************
  Include
 ********************/
#include "mu_prolog.hpp"

/********************
  Decl declaration
 ********************/

class mu_1_ProcId: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_ProcId& val){ return value(val.value());};
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_ProcId& val)
    {
      if (val.defined())
	return ( s << mu_1_ProcId::values[ int(val) - 1 ] );
      else
	return ( s << "Undefined" );
    };

  mu_1_ProcId (const char *name, int os): mu__byte(1, 2, 2, name, os) {};
  mu_1_ProcId (void): mu__byte(1, 2, 2) {};
  mu_1_ProcId (int val): mu__byte(1, 2, 2, "Parameter or function result.", 0)
    { operator=(val); };
  const char * Name() { return values[ value() -1]; };
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ value() - 1] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
friend int CompareWeight(mu_1_ProcId& a, mu_1_ProcId& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
};
const char *mu_1_ProcId::values[] =
  { "ProcId_1","ProcId_2",NULL };

/*** end scalarset declaration ***/
mu_1_ProcId mu_1_ProcId_undefined_var;

class mu_1_MemoryId: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_MemoryId& val){ return value(val.value());};
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_MemoryId& val)
    {
      if (val.defined())
	return ( s << mu_1_MemoryId::values[ int(val) - 3 ] );
      else
	return ( s << "Undefined" );
    };

  mu_1_MemoryId (const char *name, int os): mu__byte(3, 3, 1, name, os) {};
  mu_1_MemoryId (void): mu__byte(3, 3, 1) {};
  mu_1_MemoryId (int val): mu__byte(3, 3, 1, "Parameter or function result.", 0)
    { operator=(val); };
  const char * Name() { return values[ value() -3]; };
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ value() - 3] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
friend int CompareWeight(mu_1_MemoryId& a, mu_1_MemoryId& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
};
const char *mu_1_MemoryId::values[] =
  { "MemoryId_1",NULL };

/*** end scalarset declaration ***/
mu_1_MemoryId mu_1_MemoryId_undefined_var;

class mu_1_NodeId: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_NodeId& val) { return value(val.value()); };
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_NodeId& val)
    {
      if (val.defined())
	return ( s << mu_1_NodeId::values[ val.indexvalue() ] );
      else
	return ( s << "Undefined" );
    };

  // note thate lb and ub are not used if we have byte compacted state.
  mu_1_NodeId (const char *name, int os): mu__byte(0, 2, 2, name, os) {};
  mu_1_NodeId (void): mu__byte(0, 2, 2) {};
  mu_1_NodeId (int val): mu__byte(0, 2, 2, "Parameter or function result.", 0)
    { operator=(val); };
  int value() const
  {
    int val = mu__byte::value();
    // val == -1 if value undefined
    // we can return it since no enum/scalarsetid will have value -1
    if (val == -1) return -1;
    if (val <= 1) return val+1;
    if (val <= 2) return val+1;
  }
  inline int value(int val)
  {
    if (val == -1) { undefine(); return -1; }
    if ((val >= 1) && (val <= 2)) return (mu__byte::value(val-1)+1);
    if ((val >= 3) && (val <= 3)) return (mu__byte::value(val-1)+1);
  }
  inline int indexvalue() const
  {
    return mu__byte::value();
  };
  inline int unionassign(int val)
  {
    return mu__byte::value(val);
  };
  const char * Name() { return values[ indexvalue() ]; };
friend int CompareWeight(mu_1_NodeId& a, mu_1_NodeId& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ indexvalue() ] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
};
const char *mu_1_NodeId::values[] = {"ProcId_1","ProcId_2","MemoryId_1",NULL };

/*** end union declaration ***/
mu_1_NodeId mu_1_NodeId_undefined_var;

class mu_1_MemoryLineId: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_MemoryLineId& val){ return value(val.value());};
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_MemoryLineId& val)
    {
      if (val.defined())
	return ( s << mu_1_MemoryLineId::values[ int(val) - 4 ] );
      else
	return ( s << "Undefined" );
    };

  mu_1_MemoryLineId (const char *name, int os): mu__byte(4, 4, 1, name, os) {};
  mu_1_MemoryLineId (void): mu__byte(4, 4, 1) {};
  mu_1_MemoryLineId (int val): mu__byte(4, 4, 1, "Parameter or function result.", 0)
    { operator=(val); };
  const char * Name() { return values[ value() -4]; };
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ value() - 4] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
friend int CompareWeight(mu_1_MemoryLineId& a, mu_1_MemoryLineId& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
};
const char *mu_1_MemoryLineId::values[] =
  { "MemoryLineId_1",NULL };

/*** end scalarset declaration ***/
mu_1_MemoryLineId mu_1_MemoryLineId_undefined_var;

class mu_1_CacheLineId: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_CacheLineId& val){ return value(val.value());};
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_CacheLineId& val)
    {
      if (val.defined())
	return ( s << mu_1_CacheLineId::values[ int(val) - 5 ] );
      else
	return ( s << "Undefined" );
    };

  mu_1_CacheLineId (const char *name, int os): mu__byte(5, 5, 1, name, os) {};
  mu_1_CacheLineId (void): mu__byte(5, 5, 1) {};
  mu_1_CacheLineId (int val): mu__byte(5, 5, 1, "Parameter or function result.", 0)
    { operator=(val); };
  const char * Name() { return values[ value() -5]; };
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ value() - 5] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
friend int CompareWeight(mu_1_CacheLineId& a, mu_1_CacheLineId& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
};
const char *mu_1_CacheLineId::values[] =
  { "CacheLineId_1",NULL };

/*** end scalarset declaration ***/
mu_1_CacheLineId mu_1_CacheLineId_undefined_var;

class mu_1_Data: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_Data& val){ return value(val.value());};
  inline operator int() const { return value(); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_Data& val)
    {
      if (val.defined())
	return ( s << mu_1_Data::values[ int(val) - 6 ] );
      else
	return ( s << "Undefined" );
    };

  mu_1_Data (const char *name, int os): mu__byte(6, 6, 1, name, os) {};
  mu_1_Data (void): mu__byte(6, 6, 1) {};
  mu_1_Data (int val): mu__byte(6, 6, 1, "Parameter or function result.", 0)
    { operator=(val); };
  const char * Name() { return values[ value() -6]; };
  virtual void print()
    {
      if (defined()) cout << name << ':' << values[ value() - 6] << '\n';
      else cout << name << ":Undefined\n";
    };
  void print_statistic() {};
friend int CompareWeight(mu_1_Data& a, mu_1_Data& b)
{
  if (!a.defined() && b.defined())
    return -1;
  else if (a.defined() && !b.defined())
    return 1;
  else
    return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
};
const char *mu_1_Data::values[] =
  { "Data_1",NULL };

/*** end scalarset declaration ***/
mu_1_Data mu_1_Data_undefined_var;

class mu_1_AccessCommandsReq: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_AccessCommandsReq& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_AccessCommandsReq& val)
  {
    if (val.defined())
      return ( s << mu_1_AccessCommandsReq::values[ int(val) - 7] );
    else return ( s << "Undefined" );
  };

  mu_1_AccessCommandsReq (const char *name, int os): mu__byte(7, 9, 2, name, os) {};
  mu_1_AccessCommandsReq (void): mu__byte(7, 9, 2) {};
  mu_1_AccessCommandsReq (int val): mu__byte(7, 9, 2, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -7]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -7] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_AccessCommandsReq::values[] = {"SC_MREAD","SC_MWRITE64","SC_CREAD",NULL };

/*** end of enum declaration ***/
mu_1_AccessCommandsReq mu_1_AccessCommandsReq_undefined_var;

class mu_1_AccessCommandsRes: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_AccessCommandsRes& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_AccessCommandsRes& val)
  {
    if (val.defined())
      return ( s << mu_1_AccessCommandsRes::values[ int(val) - 10] );
    else return ( s << "Undefined" );
  };

  mu_1_AccessCommandsRes (const char *name, int os): mu__byte(10, 11, 2, name, os) {};
  mu_1_AccessCommandsRes (void): mu__byte(10, 11, 2) {};
  mu_1_AccessCommandsRes (int val): mu__byte(10, 11, 2, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -10]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -10] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_AccessCommandsRes::values[] = {"SC_RESP00","SC_RESP64",NULL };

/*** end of enum declaration ***/
mu_1_AccessCommandsRes mu_1_AccessCommandsRes_undefined_var;

class mu_1_MemoryCacheCommands: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_MemoryCacheCommands& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_MemoryCacheCommands& val)
  {
    if (val.defined())
      return ( s << mu_1_MemoryCacheCommands::values[ int(val) - 12] );
    else return ( s << "Undefined" );
  };

  mu_1_MemoryCacheCommands (const char *name, int os): mu__byte(12, 70, 6, name, os) {};
  mu_1_MemoryCacheCommands (void): mu__byte(12, 70, 6) {};
  mu_1_MemoryCacheCommands (int val): mu__byte(12, 70, 6, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -12]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -12] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_MemoryCacheCommands::values[] = {"MC_PASS_HEAD","MC_CACHE_FRESH","MC_CACHE_CLEAN","MC_CACHE_DIRTY","MC_LOCK_CLEAR","MC_LOCK_SET","MC_ATTACH_TO_GONE","MC_ATTACH_TO_LIST","MC_LIST_TO_GONE","MC_FRESH_TO_HOME","MC_LIST_TO_HOME","MC_LIST_TO_FRESH","MC_WASH_TO_FRESH","CC_LOCK_CLEAR","CC_PEND_VALID","CC_FRESH_INVALID","CC_NEXT_SSAVE","CC_PREV_VMID","CC_PREV_VTAIL","CC_VALID_INVALID","CC_TAIL_INVALID","CC_NEXT_VMID","CC_NEXT_FHEAD","CC_NEXT_CHEAD","CC_NEXT_DHEAD","CC_HEADD_TO_STALE","CC_HEADV_TO_STALE","CC_TAILD_TO_STALE","CC_TAILV_TO_STALE","CC_PREV_IMID","CC_PREV_DTAIL","CC_PREV_STAIL","CC_PREV_ITAIL","CC_NEXT_IMID","CC_NEXT_VHEAD","CC_NEXT_SHEAD","CC_NEXT_IHEAD","CC_LOCK_SET","CC_COPY_VALID","CC_COPY_STALE","CC_COPY_QOLB","CC_HEADE_TO_DIRTY","CC_TAILE_TO_DIRTY","CC_HEADE_TO_STALE0","CC_HEADE_TO_STALE1","CC_TAILE_TO_STALE0","CC_TAILE_TO_STALE1","CC_HEADU_TO_NEED0","CC_HEADU_TO_NEED1","CC_TAILU_TO_NEED0","CC_TAILU_TO_NEED1","CC_NEXT_EHEAD","CC_NEXT_NHEAD","CC_PREV_ETAIL","CC_PREV_NTAIL","CC_PREVI_TO_USED","CC_PREVI_TO_NEED","CC_TAILI_TO_USED","CC_TAILI_TO_NEED",NULL };

/*** end of enum declaration ***/
mu_1_MemoryCacheCommands mu_1_MemoryCacheCommands_undefined_var;

class mu_1_SStatValues: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_SStatValues& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_SStatValues& val)
  {
    if (val.defined())
      return ( s << mu_1_SStatValues::values[ int(val) - 71] );
    else return ( s << "Undefined" );
  };

  mu_1_SStatValues (const char *name, int os): mu__byte(71, 78, 4, name, os) {};
  mu_1_SStatValues (void): mu__byte(71, 78, 4) {};
  mu_1_SStatValues (int val): mu__byte(71, 78, 4, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -71]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -71] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_SStatValues::values[] = {"RESP_NORMAL","RESP_ADVICE","RESP_GONE","RESP_LOCKED","RESP_CONFLICT","RESP_DATA","RESP_TYPE","RESP_ADDRESS",NULL };

/*** end of enum declaration ***/
mu_1_SStatValues mu_1_SStatValues_undefined_var;

class mu_1_MemoryCacheStates: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_MemoryCacheStates& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_MemoryCacheStates& val)
  {
    if (val.defined())
      return ( s << mu_1_MemoryCacheStates::values[ int(val) - 79] );
    else return ( s << "Undefined" );
  };

  mu_1_MemoryCacheStates (const char *name, int os): mu__byte(79, 228, 8, name, os) {};
  mu_1_MemoryCacheStates (void): mu__byte(79, 228, 8) {};
  mu_1_MemoryCacheStates (int val): mu__byte(79, 228, 8, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -79]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -79] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_MemoryCacheStates::values[] = {"MS_HOME","MS_FRESH","MS_GONE","MS_WASH","CS_INVALID","CS_OD_RETN_IN","CS_OD_spin_IN","CS_QUEUED_FRESH","CS_ONLY_DIRTY","CS_QUEUED_DIRTY","CS_HEAD_DIRTY","CS_QUEUED_CLEAN","CS_QUEUED_MODS","CS_PENDING","CS_QUEUED_JUNK","CS_MV_forw_MV","CS_MV_back_IN","CS_MID_VALID","CS_MID_COPY","CS_ONLYQ_DIRTY","CS_HD_INVAL_OD","CS_MI_forw_MI","CS_MI_back_IN","CS_HEAD_IDLE","CS_MID_IDLE","CS_TAIL_VALID","CS_TAIL_COPY","CS_OF_retn_IN","CS_QUEUED_HOME","CS_HX_FORW_HX","CS_HX_FORW_OX","CS_ONLY_FRESH","CS_OF_MODS_OD","CS_HX_INVAL_OX","CS_HEAD_FRESH","CS_HF_MODS_HD","CS_TO_INVALID","CS_TV_back_IN","CS_QF_FLUSH_IN","CS_LOCAL_CLEAN","CS_HW_WASH_HF","CS_ONLYP_DIRTY","CS_HEAD_STALE0","CS_HEAD_STALE1","CS_HX_retn_IN","CS_HEAD_VALID","CS_LOCAL_DIRTY","CS_H0_PEND_HX","CS_H1_PEND_HX","CS_HX_PEND_HX","CS_OC_retn_IN","CS_HEAD_CLEAN","CS_ONLY_CLEAN","CS_HX_XXXX_OD","CS_TS0_Move_TE","CS_TS1_Move_TE","CS_TS_copy_TV","CS_TV_mark_TS","CS_HEAD_WASH","CS_TX_XXXX_OD","CS_TV_mark_TE","CS_TD_back_IN","CS_TS_back_IN","CS_TE_back_IN","CS_TAIL_DIRTY","CS_TAIL_EXCL","CS_TD_mark_TE","CS_TAIL_IDLE","CS_TI_back_IN","CS_TAIL_STALE0","CS_TAIL_STALE1","CS_HV_MARK_HE","CS_HEAD_EXCL","CS_HD_MARK_HE","CS_TN_back_IN","CS_TN_send_TS","CS_TN_send_TI","CS_OD_CLEAN_OC","CS_ONLY_USED","CS_TAIL_NEED","CS_HS0_MOVE_HE","CS_HS1_MOVE_HE","CS_HS_COPY_HV","CS_HV_MARK_HS","CS_HD_CLEAN_HC","CS_HEAD_NEED","CS_SAVE_STALE","CS_SS_next_IN","CS_HN_SEND_HS","CS_HN_SEND_HI","CS_HD_WASH_HF","CS_TAIL_USED","CS_HS0_MOVE_HI","CS_HS1_MOVE_HI","CS_TS0_Move_TI","CS_TS1_Move_TI","CS_HEAD_USED","CI_HEAD_DIRTY","CI_HEAD_CLEAN","CI_HEAD_WASH","CI_HEAD_MODS","CI_HEADQ_DIRTY","CI_HEADQ_EXCL","CI_HD_WASH_HF","CI_HW_WASH_HF","CI_QUEUED_CLEAN","CI_QUEUED_FRESH","CI_QUEUED_DIRTY","CI_ONLY_EXCL","CI_HEAD_EXCL","CI_TAIL_EXCL","CI_QD_MODS_OU","CI_HD_MODS_OU","CI_HD_FLUSH_IN","CI_HC_FLUSH_IN","CI_LD_FLUSH_IN","CI_OD_PURGE_IN","CI_HN_PURGE_IN","CI_HE_PURGE_IN","CI_HD_PURGE_IN","CI_LD_CLEAN_LC","CI_OD_CLEAN_OC","CI_HD_CLEAN_HC","CI_HN_CLEAN_OC","CI_HE_CLEAN_OC","CI_HD_MODS_HE","CI_HD_MODS_HU","CI_TD_MODS_TE","CI_TD_MODS_TU","CI_HN_DEQOLB_HS","CI_TN_DEQOLB_TS","CI_HN_REQOLB_HI","CI_TN_REQOLB_TI","CI_HI_DELETE_IN","CI_MI_DELETE_IN","CI_TI_DELETE_IN","CI_CHECK_HOME","CI_HF_FLUSH_IN","CI_QF_FLUSH_IN","CI_QD_FLUSH_IN","CI_OD_FLUSH_IN","CI_OC_FLUSH_IN","CI_OF_FLUSH_IN","CI_HN_FLUSH_IN","CI_HE_FLUSH_IN","CI_WRITE_CHECK","CI_WC_DONE_IN","CI_READ_FRESH","CI_ONLY_CLEAN","CI_ONLY_DIRTY",NULL };

/*** end of enum declaration ***/
mu_1_MemoryCacheStates mu_1_MemoryCacheStates_undefined_var;

class mu_1_DataFlags: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_DataFlags& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_DataFlags& val)
  {
    if (val.defined())
      return ( s << mu_1_DataFlags::values[ int(val) - 229] );
    else return ( s << "Undefined" );
  };

  mu_1_DataFlags (const char *name, int os): mu__byte(229, 239, 4, name, os) {};
  mu_1_DataFlags (void): mu__byte(229, 239, 4) {};
  mu_1_DataFlags (int val): mu__byte(229, 239, 4, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -229]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -229] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_DataFlags::values[] = {"NORM_NONE","NORM_DATA","NORM_NULL","NORM_SKIP","FULL_NONE","FULL_DATA","FULL_NULL","HUGE_TAGS","LOCK_DATA","MISS_MORE","MISS_NONE",NULL };

/*** end of enum declaration ***/
mu_1_DataFlags mu_1_DataFlags_undefined_var;

class mu_1_AccessTypes: public mu__byte
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_AccessTypes& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_AccessTypes& val)
  {
    if (val.defined())
      return ( s << mu_1_AccessTypes::values[ int(val) - 240] );
    else return ( s << "Undefined" );
  };

  mu_1_AccessTypes (const char *name, int os): mu__byte(240, 255, 5, name, os) {};
  mu_1_AccessTypes (void): mu__byte(240, 255, 5) {};
  mu_1_AccessTypes (int val): mu__byte(240, 255, 5, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -240]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -240] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_AccessTypes::values[] = {"CT_ONLY_DIRTY","CT_HEAD_DIRTY","CT_MID_VALID","CT_HEAD_IDLE","CT_ONLY_FRESH","CT_HEAD_FRESH","CT_ONLYP_DIRTY","CT_HEAD_RETN","CT_HEAD_CLEAN","CT_HEAD_WASH","CT_TAIL_EXCL","CT_HEAD_EXCL","CT_ONLY_USED","CT_HEAD_NEED","CT_TAIL_USED","CT_HEAD_USED",NULL };

/*** end of enum declaration ***/
mu_1_AccessTypes mu_1_AccessTypes_undefined_var;

class mu_1_FetchOptions: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_FetchOptions& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_FetchOptions& val)
  {
    if (val.defined())
      return ( s << mu_1_FetchOptions::values[ int(val) - 256] );
    else return ( s << "Undefined" );
  };

  mu_1_FetchOptions (const char *name, int os): mu__long(256, 258, 2, name, os) {};
  mu_1_FetchOptions (void): mu__long(256, 258, 2) {};
  mu_1_FetchOptions (int val): mu__long(256, 258, 2, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -256]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -256] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_FetchOptions::values[] = {"CO_FETCH","CO_LOAD","CO_STORE",NULL };

/*** end of enum declaration ***/
mu_1_FetchOptions mu_1_FetchOptions_undefined_var;

class mu_1_TransactStatus: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_TransactStatus& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_TransactStatus& val)
  {
    if (val.defined())
      return ( s << mu_1_TransactStatus::values[ int(val) - 259] );
    else return ( s << "Undefined" );
  };

  mu_1_TransactStatus (const char *name, int os): mu__long(259, 279, 5, name, os) {};
  mu_1_TransactStatus (void): mu__long(259, 279, 5) {};
  mu_1_TransactStatus (int val): mu__long(259, 279, 5, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -259]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -259] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_TransactStatus::values[] = {"TS_NORM_NULL","TS_NORM_CODE","TS_RESP_FAKE","TS_RESP_CODE","TS_CORE_JUNK","TS_RESP_SIZE","TS_RESP_DIFF","TS_LINK_DEAD","TS_LOST_TIDS","TS_TIME_TIDS","TS_SEND_TYPE","TS_SEND_ADDR","TS_TIME_BUSY","TS_TIME_RESP","TS_RESP_IDS","TS_RESP_BAD","TS_LOCK_BEFORE","TS_LOCK_DURING","TS_MTAG_STATE","TS_CTAG_STATE","TS_CODE_NULL",NULL };

/*** end of enum declaration ***/
mu_1_TransactStatus mu_1_TransactStatus_undefined_var;

class mu_1_FindFlags: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_FindFlags& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_FindFlags& val)
  {
    if (val.defined())
      return ( s << mu_1_FindFlags::values[ int(val) - 280] );
    else return ( s << "Undefined" );
  };

  mu_1_FindFlags (const char *name, int os): mu__long(280, 286, 3, name, os) {};
  mu_1_FindFlags (void): mu__long(280, 286, 3) {};
  mu_1_FindFlags (int val): mu__long(280, 286, 3, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -280]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -280] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_FindFlags::values[] = {"FF_FIND","FF_WAIT","FF_LOAD","FF_STORE","FF_LOCK","FF_ENQOLB","FF_INDEX",NULL };

/*** end of enum declaration ***/
mu_1_FindFlags mu_1_FindFlags_undefined_var;

class mu_1_BypassOptions: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_BypassOptions& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_BypassOptions& val)
  {
    if (val.defined())
      return ( s << mu_1_BypassOptions::values[ int(val) - 287] );
    else return ( s << "Undefined" );
  };

  mu_1_BypassOptions (const char *name, int os): mu__long(287, 289, 2, name, os) {};
  mu_1_BypassOptions (void): mu__long(287, 289, 2) {};
  mu_1_BypassOptions (int val): mu__long(287, 289, 2, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -287]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -287] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_BypassOptions::values[] = {"CU_BYPASS","CU_LOCAL","CU_GLOBAL",NULL };

/*** end of enum declaration ***/
mu_1_BypassOptions mu_1_BypassOptions_undefined_var;

class mu_1_StableGroups: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_StableGroups& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_StableGroups& val)
  {
    if (val.defined())
      return ( s << mu_1_StableGroups::values[ int(val) - 290] );
    else return ( s << "Undefined" );
  };

  mu_1_StableGroups (const char *name, int os): mu__long(290, 294, 3, name, os) {};
  mu_1_StableGroups (void): mu__long(290, 294, 3) {};
  mu_1_StableGroups (int val): mu__long(290, 294, 3, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -290]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -290] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_StableGroups::values[] = {"SG_NONE","SG_INVALID","SG_STALE","SG_GLOBAL","SG_LOCAL",NULL };

/*** end of enum declaration ***/
mu_1_StableGroups mu_1_StableGroups_undefined_var;

class mu_1_AttachStatus
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_MemoryCacheStates mu_cState;
  mu_1_NodeId mu_backId;
  mu_1_AttachStatus ( const char *n, int os ) { set_self(n,os); };
  mu_1_AttachStatus ( void ) {};

  virtual ~mu_1_AttachStatus(); 
friend int CompareWeight(mu_1_AttachStatus& a, mu_1_AttachStatus& b)
  {
    int w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_AttachStatus& a, mu_1_AttachStatus& b)
  {
    int w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = Compare(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_cState.MultisetSort();
    mu_backId.MultisetSort();
  }
  void print_statistic()
  {
    mu_cState.print_statistic();
    mu_backId.print_statistic();
  }
  void clear() {
    mu_cState.clear();
    mu_backId.clear();
 };
  void undefine() {
    mu_cState.undefine();
    mu_backId.undefine();
 };
  void reset() {
    mu_cState.reset();
    mu_backId.reset();
 };
  void print() {
    mu_cState.print();
    mu_backId.print();
  };
  void print_diff(state *prevstate) {
    mu_cState.print_diff(prevstate);
    mu_backId.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_cState.to_state(thestate);
    mu_backId.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_AttachStatus& operator= (const mu_1_AttachStatus& from) {
    mu_cState.value(from.mu_cState.value());
    mu_backId.value(from.mu_backId.value());
    return *this;
  };
};

  void mu_1_AttachStatus::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_AttachStatus::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_AttachStatus::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_cState.set_self_2(name, ".cState", os + 0 ); else mu_cState.set_self_2(NULL, NULL, 0);
  if (name) mu_backId.set_self_2(name, ".backId", os + 8 ); else mu_backId.set_self_2(NULL, NULL, 0);
}

mu_1_AttachStatus::~mu_1_AttachStatus()
{
}

/*** end record declaration ***/
mu_1_AttachStatus mu_1_AttachStatus_undefined_var;

class mu_1_ReqPacket
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_NodeId mu_targetId;
  mu_1_AccessCommandsReq mu_cmd;
  mu_1_NodeId mu_sourceId;
  mu_1_MemoryLineId mu_offset;
  mu_1_MemoryCacheCommands mu_mopCop;
  mu_0_boolean mu_s;
  mu_0_boolean mu_eh;
  mu_1_Data mu_data;
  mu_1_NodeId mu_newId;
  mu_1_NodeId mu_memId;
  mu_1_ReqPacket ( const char *n, int os ) { set_self(n,os); };
  mu_1_ReqPacket ( void ) {};

  virtual ~mu_1_ReqPacket(); 
friend int CompareWeight(mu_1_ReqPacket& a, mu_1_ReqPacket& b)
  {
    int w;
    w = CompareWeight(a.mu_targetId, b.mu_targetId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cmd, b.mu_cmd);
    if (w!=0) return w;
    w = CompareWeight(a.mu_sourceId, b.mu_sourceId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_offset, b.mu_offset);
    if (w!=0) return w;
    w = CompareWeight(a.mu_mopCop, b.mu_mopCop);
    if (w!=0) return w;
    w = CompareWeight(a.mu_s, b.mu_s);
    if (w!=0) return w;
    w = CompareWeight(a.mu_eh, b.mu_eh);
    if (w!=0) return w;
    w = CompareWeight(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = CompareWeight(a.mu_newId, b.mu_newId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_ReqPacket& a, mu_1_ReqPacket& b)
  {
    int w;
    w = Compare(a.mu_targetId, b.mu_targetId);
    if (w!=0) return w;
    w = Compare(a.mu_cmd, b.mu_cmd);
    if (w!=0) return w;
    w = Compare(a.mu_sourceId, b.mu_sourceId);
    if (w!=0) return w;
    w = Compare(a.mu_offset, b.mu_offset);
    if (w!=0) return w;
    w = Compare(a.mu_mopCop, b.mu_mopCop);
    if (w!=0) return w;
    w = Compare(a.mu_s, b.mu_s);
    if (w!=0) return w;
    w = Compare(a.mu_eh, b.mu_eh);
    if (w!=0) return w;
    w = Compare(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = Compare(a.mu_newId, b.mu_newId);
    if (w!=0) return w;
    w = Compare(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_targetId.MultisetSort();
    mu_cmd.MultisetSort();
    mu_sourceId.MultisetSort();
    mu_offset.MultisetSort();
    mu_mopCop.MultisetSort();
    mu_s.MultisetSort();
    mu_eh.MultisetSort();
    mu_data.MultisetSort();
    mu_newId.MultisetSort();
    mu_memId.MultisetSort();
  }
  void print_statistic()
  {
    mu_targetId.print_statistic();
    mu_cmd.print_statistic();
    mu_sourceId.print_statistic();
    mu_offset.print_statistic();
    mu_mopCop.print_statistic();
    mu_s.print_statistic();
    mu_eh.print_statistic();
    mu_data.print_statistic();
    mu_newId.print_statistic();
    mu_memId.print_statistic();
  }
  void clear() {
    mu_targetId.clear();
    mu_cmd.clear();
    mu_sourceId.clear();
    mu_offset.clear();
    mu_mopCop.clear();
    mu_s.clear();
    mu_eh.clear();
    mu_data.clear();
    mu_newId.clear();
    mu_memId.clear();
 };
  void undefine() {
    mu_targetId.undefine();
    mu_cmd.undefine();
    mu_sourceId.undefine();
    mu_offset.undefine();
    mu_mopCop.undefine();
    mu_s.undefine();
    mu_eh.undefine();
    mu_data.undefine();
    mu_newId.undefine();
    mu_memId.undefine();
 };
  void reset() {
    mu_targetId.reset();
    mu_cmd.reset();
    mu_sourceId.reset();
    mu_offset.reset();
    mu_mopCop.reset();
    mu_s.reset();
    mu_eh.reset();
    mu_data.reset();
    mu_newId.reset();
    mu_memId.reset();
 };
  void print() {
    mu_targetId.print();
    mu_cmd.print();
    mu_sourceId.print();
    mu_offset.print();
    mu_mopCop.print();
    mu_s.print();
    mu_eh.print();
    mu_data.print();
    mu_newId.print();
    mu_memId.print();
  };
  void print_diff(state *prevstate) {
    mu_targetId.print_diff(prevstate);
    mu_cmd.print_diff(prevstate);
    mu_sourceId.print_diff(prevstate);
    mu_offset.print_diff(prevstate);
    mu_mopCop.print_diff(prevstate);
    mu_s.print_diff(prevstate);
    mu_eh.print_diff(prevstate);
    mu_data.print_diff(prevstate);
    mu_newId.print_diff(prevstate);
    mu_memId.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_targetId.to_state(thestate);
    mu_cmd.to_state(thestate);
    mu_sourceId.to_state(thestate);
    mu_offset.to_state(thestate);
    mu_mopCop.to_state(thestate);
    mu_s.to_state(thestate);
    mu_eh.to_state(thestate);
    mu_data.to_state(thestate);
    mu_newId.to_state(thestate);
    mu_memId.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_ReqPacket& operator= (const mu_1_ReqPacket& from) {
    mu_targetId.value(from.mu_targetId.value());
    mu_cmd.value(from.mu_cmd.value());
    mu_sourceId.value(from.mu_sourceId.value());
    mu_offset.value(from.mu_offset.value());
    mu_mopCop.value(from.mu_mopCop.value());
    mu_s.value(from.mu_s.value());
    mu_eh.value(from.mu_eh.value());
    mu_data.value(from.mu_data.value());
    mu_newId.value(from.mu_newId.value());
    mu_memId.value(from.mu_memId.value());
    return *this;
  };
};

  void mu_1_ReqPacket::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_ReqPacket::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_ReqPacket::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_targetId.set_self_2(name, ".targetId", os + 0 ); else mu_targetId.set_self_2(NULL, NULL, 0);
  if (name) mu_cmd.set_self_2(name, ".cmd", os + 2 ); else mu_cmd.set_self_2(NULL, NULL, 0);
  if (name) mu_sourceId.set_self_2(name, ".sourceId", os + 4 ); else mu_sourceId.set_self_2(NULL, NULL, 0);
  if (name) mu_offset.set_self_2(name, ".offset", os + 6 ); else mu_offset.set_self_2(NULL, NULL, 0);
  if (name) mu_mopCop.set_self_2(name, ".mopCop", os + 7 ); else mu_mopCop.set_self_2(NULL, NULL, 0);
  if (name) mu_s.set_self_2(name, ".s", os + 13 ); else mu_s.set_self_2(NULL, NULL, 0);
  if (name) mu_eh.set_self_2(name, ".eh", os + 15 ); else mu_eh.set_self_2(NULL, NULL, 0);
  if (name) mu_data.set_self_2(name, ".data", os + 17 ); else mu_data.set_self_2(NULL, NULL, 0);
  if (name) mu_newId.set_self_2(name, ".newId", os + 18 ); else mu_newId.set_self_2(NULL, NULL, 0);
  if (name) mu_memId.set_self_2(name, ".memId", os + 20 ); else mu_memId.set_self_2(NULL, NULL, 0);
}

mu_1_ReqPacket::~mu_1_ReqPacket()
{
}

/*** end record declaration ***/
mu_1_ReqPacket mu_1_ReqPacket_undefined_var;

class mu_1_ResPacket
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_AccessCommandsRes mu_cmd;
  mu_0_boolean mu_cn;
  mu_0_boolean mu_co;
  mu_1_MemoryCacheStates mu_mCState;
  mu_1_Data mu_data;
  mu_1_NodeId mu_forwId;
  mu_1_NodeId mu_backId;
  mu_1_ResPacket ( const char *n, int os ) { set_self(n,os); };
  mu_1_ResPacket ( void ) {};

  virtual ~mu_1_ResPacket(); 
friend int CompareWeight(mu_1_ResPacket& a, mu_1_ResPacket& b)
  {
    int w;
    w = CompareWeight(a.mu_cmd, b.mu_cmd);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cn, b.mu_cn);
    if (w!=0) return w;
    w = CompareWeight(a.mu_co, b.mu_co);
    if (w!=0) return w;
    w = CompareWeight(a.mu_mCState, b.mu_mCState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = CompareWeight(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_ResPacket& a, mu_1_ResPacket& b)
  {
    int w;
    w = Compare(a.mu_cmd, b.mu_cmd);
    if (w!=0) return w;
    w = Compare(a.mu_cn, b.mu_cn);
    if (w!=0) return w;
    w = Compare(a.mu_co, b.mu_co);
    if (w!=0) return w;
    w = Compare(a.mu_mCState, b.mu_mCState);
    if (w!=0) return w;
    w = Compare(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = Compare(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = Compare(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_cmd.MultisetSort();
    mu_cn.MultisetSort();
    mu_co.MultisetSort();
    mu_mCState.MultisetSort();
    mu_data.MultisetSort();
    mu_forwId.MultisetSort();
    mu_backId.MultisetSort();
  }
  void print_statistic()
  {
    mu_cmd.print_statistic();
    mu_cn.print_statistic();
    mu_co.print_statistic();
    mu_mCState.print_statistic();
    mu_data.print_statistic();
    mu_forwId.print_statistic();
    mu_backId.print_statistic();
  }
  void clear() {
    mu_cmd.clear();
    mu_cn.clear();
    mu_co.clear();
    mu_mCState.clear();
    mu_data.clear();
    mu_forwId.clear();
    mu_backId.clear();
 };
  void undefine() {
    mu_cmd.undefine();
    mu_cn.undefine();
    mu_co.undefine();
    mu_mCState.undefine();
    mu_data.undefine();
    mu_forwId.undefine();
    mu_backId.undefine();
 };
  void reset() {
    mu_cmd.reset();
    mu_cn.reset();
    mu_co.reset();
    mu_mCState.reset();
    mu_data.reset();
    mu_forwId.reset();
    mu_backId.reset();
 };
  void print() {
    mu_cmd.print();
    mu_cn.print();
    mu_co.print();
    mu_mCState.print();
    mu_data.print();
    mu_forwId.print();
    mu_backId.print();
  };
  void print_diff(state *prevstate) {
    mu_cmd.print_diff(prevstate);
    mu_cn.print_diff(prevstate);
    mu_co.print_diff(prevstate);
    mu_mCState.print_diff(prevstate);
    mu_data.print_diff(prevstate);
    mu_forwId.print_diff(prevstate);
    mu_backId.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_cmd.to_state(thestate);
    mu_cn.to_state(thestate);
    mu_co.to_state(thestate);
    mu_mCState.to_state(thestate);
    mu_data.to_state(thestate);
    mu_forwId.to_state(thestate);
    mu_backId.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_ResPacket& operator= (const mu_1_ResPacket& from) {
    mu_cmd.value(from.mu_cmd.value());
    mu_cn.value(from.mu_cn.value());
    mu_co.value(from.mu_co.value());
    mu_mCState.value(from.mu_mCState.value());
    mu_data.value(from.mu_data.value());
    mu_forwId.value(from.mu_forwId.value());
    mu_backId.value(from.mu_backId.value());
    return *this;
  };
};

  void mu_1_ResPacket::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_ResPacket::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_ResPacket::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_cmd.set_self_2(name, ".cmd", os + 0 ); else mu_cmd.set_self_2(NULL, NULL, 0);
  if (name) mu_cn.set_self_2(name, ".cn", os + 2 ); else mu_cn.set_self_2(NULL, NULL, 0);
  if (name) mu_co.set_self_2(name, ".co", os + 4 ); else mu_co.set_self_2(NULL, NULL, 0);
  if (name) mu_mCState.set_self_2(name, ".mCState", os + 6 ); else mu_mCState.set_self_2(NULL, NULL, 0);
  if (name) mu_data.set_self_2(name, ".data", os + 14 ); else mu_data.set_self_2(NULL, NULL, 0);
  if (name) mu_forwId.set_self_2(name, ".forwId", os + 15 ); else mu_forwId.set_self_2(NULL, NULL, 0);
  if (name) mu_backId.set_self_2(name, ".backId", os + 17 ); else mu_backId.set_self_2(NULL, NULL, 0);
}

mu_1_ResPacket::~mu_1_ResPacket()
{
}

/*** end record declaration ***/
mu_1_ResPacket mu_1_ResPacket_undefined_var;

class mu_1_MemoryLine
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_MemoryCacheStates mu_mState;
  mu_1_NodeId mu_forwId;
  mu_1_Data mu_data;
  mu_1_MemoryLine ( const char *n, int os ) { set_self(n,os); };
  mu_1_MemoryLine ( void ) {};

  virtual ~mu_1_MemoryLine(); 
friend int CompareWeight(mu_1_MemoryLine& a, mu_1_MemoryLine& b)
  {
    int w;
    w = CompareWeight(a.mu_mState, b.mu_mState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_data, b.mu_data);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_MemoryLine& a, mu_1_MemoryLine& b)
  {
    int w;
    w = Compare(a.mu_mState, b.mu_mState);
    if (w!=0) return w;
    w = Compare(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = Compare(a.mu_data, b.mu_data);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_mState.MultisetSort();
    mu_forwId.MultisetSort();
    mu_data.MultisetSort();
  }
  void print_statistic()
  {
    mu_mState.print_statistic();
    mu_forwId.print_statistic();
    mu_data.print_statistic();
  }
  void clear() {
    mu_mState.clear();
    mu_forwId.clear();
    mu_data.clear();
 };
  void undefine() {
    mu_mState.undefine();
    mu_forwId.undefine();
    mu_data.undefine();
 };
  void reset() {
    mu_mState.reset();
    mu_forwId.reset();
    mu_data.reset();
 };
  void print() {
    mu_mState.print();
    mu_forwId.print();
    mu_data.print();
  };
  void print_diff(state *prevstate) {
    mu_mState.print_diff(prevstate);
    mu_forwId.print_diff(prevstate);
    mu_data.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_mState.to_state(thestate);
    mu_forwId.to_state(thestate);
    mu_data.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_MemoryLine& operator= (const mu_1_MemoryLine& from) {
    mu_mState.value(from.mu_mState.value());
    mu_forwId.value(from.mu_forwId.value());
    mu_data.value(from.mu_data.value());
    return *this;
  };
};

  void mu_1_MemoryLine::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_MemoryLine::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_MemoryLine::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_mState.set_self_2(name, ".mState", os + 0 ); else mu_mState.set_self_2(NULL, NULL, 0);
  if (name) mu_forwId.set_self_2(name, ".forwId", os + 8 ); else mu_forwId.set_self_2(NULL, NULL, 0);
  if (name) mu_data.set_self_2(name, ".data", os + 10 ); else mu_data.set_self_2(NULL, NULL, 0);
}

mu_1_MemoryLine::~mu_1_MemoryLine()
{
}

/*** end record declaration ***/
mu_1_MemoryLine mu_1_MemoryLine_undefined_var;

class mu_1__type_0
{
 public:
  mu_1_MemoryLine array[ 1 ];
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self( const char *n, int os);
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  mu_1__type_0 (const char *n, int os) { set_self(n, os); };
  mu_1__type_0 ( void ) {};
  virtual ~mu_1__type_0 ();
  mu_1_MemoryLine& operator[] (int index) /* const */
  {
#ifndef NO_RUN_TIME_CHECKING
    if ( ( index >= 4 ) && ( index <= 4 ) )
      return array[ index - 4 ];
    else
      {
	if (index==UNDEFVAL) 
	  Error.Error("Indexing to %s using an undefined value.", name);
	else
	  Error.Error("Funny index value %d for %s: MemoryLineId is internally represented from 4 to 4.\nInternal Error in Type checking.",index, name);
	return array[0];
      }
#else
    return array[ index - 4 ];
#endif
  };
  mu_1__type_0& operator= (const mu_1__type_0& from)
  {
      array[0] = from.array[0];
    return *this;
  }

friend int CompareWeight(mu_1__type_0& a, mu_1__type_0& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = CompareWeight(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
friend int Compare(mu_1__type_0& a, mu_1__type_0& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = Compare(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    for (int i=0; i<1; i++)
      array[i].MultisetSort();
  }
  void print_statistic()
  {
    for (int i=0; i<1; i++)
      array[i].print_statistic();
  }
  void clear() { for (int i = 0; i < 1; i++) array[i].clear(); };

  void undefine() { for (int i = 0; i < 1; i++) array[i].undefine(); };

  void reset() { for (int i = 0; i < 1; i++) array[i].reset(); };

  void to_state(state *thestate)
  {
    for (int i = 0; i < 1; i++)
      array[i].to_state(thestate);
  };

  void print()
  {
    for (int i = 0; i < 1; i++)
      array[i].print(); };

  void print_diff(state *prevstate)
  {
    for (int i = 0; i < 1; i++)
      array[i].print_diff(prevstate);
  };
};

  void mu_1__type_0::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1__type_0::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1__type_0::set_self( const char *n, int os)
  {
    int i=0;
    name = (char *)n;

if (n) array[i].set_self_ar(n,"MemoryLineId_1", i * 11 + os); else array[i].set_self_ar(NULL, NULL, 0); i++;
}
mu_1__type_0::~mu_1__type_0()
{
}
/*** end array declaration ***/
mu_1__type_0 mu_1__type_0_undefined_var;

class mu_1_Memory
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1__type_0 mu_line;
  mu_1_Memory ( const char *n, int os ) { set_self(n,os); };
  mu_1_Memory ( void ) {};

  virtual ~mu_1_Memory(); 
friend int CompareWeight(mu_1_Memory& a, mu_1_Memory& b)
  {
    int w;
    w = CompareWeight(a.mu_line, b.mu_line);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_Memory& a, mu_1_Memory& b)
  {
    int w;
    w = Compare(a.mu_line, b.mu_line);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_line.MultisetSort();
  }
  void print_statistic()
  {
    mu_line.print_statistic();
  }
  void clear() {
    mu_line.clear();
 };
  void undefine() {
    mu_line.undefine();
 };
  void reset() {
    mu_line.reset();
 };
  void print() {
    mu_line.print();
  };
  void print_diff(state *prevstate) {
    mu_line.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_line.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_Memory& operator= (const mu_1_Memory& from) {
    mu_line = from.mu_line;
    return *this;
  };
};

  void mu_1_Memory::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_Memory::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_Memory::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_line.set_self_2(name, ".line", os + 0 ); else mu_line.set_self_2(NULL, NULL, 0);
}

mu_1_Memory::~mu_1_Memory()
{
}

/*** end record declaration ***/
mu_1_Memory mu_1_Memory_undefined_var;

class mu_1_CacheLine
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_MemoryCacheStates mu_cState;
  mu_1_NodeId mu_forwId;
  mu_1_NodeId mu_backId;
  mu_1_NodeId mu_memId;
  mu_1_MemoryLineId mu_addrOffset;
  mu_1_Data mu_data;
  mu_1_CacheLine ( const char *n, int os ) { set_self(n,os); };
  mu_1_CacheLine ( void ) {};

  virtual ~mu_1_CacheLine(); 
friend int CompareWeight(mu_1_CacheLine& a, mu_1_CacheLine& b)
  {
    int w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_addrOffset, b.mu_addrOffset);
    if (w!=0) return w;
    w = CompareWeight(a.mu_data, b.mu_data);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_CacheLine& a, mu_1_CacheLine& b)
  {
    int w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = Compare(a.mu_forwId, b.mu_forwId);
    if (w!=0) return w;
    w = Compare(a.mu_backId, b.mu_backId);
    if (w!=0) return w;
    w = Compare(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
    w = Compare(a.mu_addrOffset, b.mu_addrOffset);
    if (w!=0) return w;
    w = Compare(a.mu_data, b.mu_data);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_cState.MultisetSort();
    mu_forwId.MultisetSort();
    mu_backId.MultisetSort();
    mu_memId.MultisetSort();
    mu_addrOffset.MultisetSort();
    mu_data.MultisetSort();
  }
  void print_statistic()
  {
    mu_cState.print_statistic();
    mu_forwId.print_statistic();
    mu_backId.print_statistic();
    mu_memId.print_statistic();
    mu_addrOffset.print_statistic();
    mu_data.print_statistic();
  }
  void clear() {
    mu_cState.clear();
    mu_forwId.clear();
    mu_backId.clear();
    mu_memId.clear();
    mu_addrOffset.clear();
    mu_data.clear();
 };
  void undefine() {
    mu_cState.undefine();
    mu_forwId.undefine();
    mu_backId.undefine();
    mu_memId.undefine();
    mu_addrOffset.undefine();
    mu_data.undefine();
 };
  void reset() {
    mu_cState.reset();
    mu_forwId.reset();
    mu_backId.reset();
    mu_memId.reset();
    mu_addrOffset.reset();
    mu_data.reset();
 };
  void print() {
    mu_cState.print();
    mu_forwId.print();
    mu_backId.print();
    mu_memId.print();
    mu_addrOffset.print();
    mu_data.print();
  };
  void print_diff(state *prevstate) {
    mu_cState.print_diff(prevstate);
    mu_forwId.print_diff(prevstate);
    mu_backId.print_diff(prevstate);
    mu_memId.print_diff(prevstate);
    mu_addrOffset.print_diff(prevstate);
    mu_data.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_cState.to_state(thestate);
    mu_forwId.to_state(thestate);
    mu_backId.to_state(thestate);
    mu_memId.to_state(thestate);
    mu_addrOffset.to_state(thestate);
    mu_data.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_CacheLine& operator= (const mu_1_CacheLine& from) {
    mu_cState.value(from.mu_cState.value());
    mu_forwId.value(from.mu_forwId.value());
    mu_backId.value(from.mu_backId.value());
    mu_memId.value(from.mu_memId.value());
    mu_addrOffset.value(from.mu_addrOffset.value());
    mu_data.value(from.mu_data.value());
    return *this;
  };
};

  void mu_1_CacheLine::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_CacheLine::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_CacheLine::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_cState.set_self_2(name, ".cState", os + 0 ); else mu_cState.set_self_2(NULL, NULL, 0);
  if (name) mu_forwId.set_self_2(name, ".forwId", os + 8 ); else mu_forwId.set_self_2(NULL, NULL, 0);
  if (name) mu_backId.set_self_2(name, ".backId", os + 10 ); else mu_backId.set_self_2(NULL, NULL, 0);
  if (name) mu_memId.set_self_2(name, ".memId", os + 12 ); else mu_memId.set_self_2(NULL, NULL, 0);
  if (name) mu_addrOffset.set_self_2(name, ".addrOffset", os + 14 ); else mu_addrOffset.set_self_2(NULL, NULL, 0);
  if (name) mu_data.set_self_2(name, ".data", os + 15 ); else mu_data.set_self_2(NULL, NULL, 0);
}

mu_1_CacheLine::~mu_1_CacheLine()
{
}

/*** end record declaration ***/
mu_1_CacheLine mu_1_CacheLine_undefined_var;

class mu_1__type_1
{
 public:
  mu_1_CacheLine array[ 1 ];
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self( const char *n, int os);
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  mu_1__type_1 (const char *n, int os) { set_self(n, os); };
  mu_1__type_1 ( void ) {};
  virtual ~mu_1__type_1 ();
  mu_1_CacheLine& operator[] (int index) /* const */
  {
#ifndef NO_RUN_TIME_CHECKING
    if ( ( index >= 5 ) && ( index <= 5 ) )
      return array[ index - 5 ];
    else
      {
	if (index==UNDEFVAL) 
	  Error.Error("Indexing to %s using an undefined value.", name);
	else
	  Error.Error("Funny index value %d for %s: CacheLineId is internally represented from 5 to 5.\nInternal Error in Type checking.",index, name);
	return array[0];
      }
#else
    return array[ index - 5 ];
#endif
  };
  mu_1__type_1& operator= (const mu_1__type_1& from)
  {
      array[0] = from.array[0];
    return *this;
  }

friend int CompareWeight(mu_1__type_1& a, mu_1__type_1& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = CompareWeight(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
friend int Compare(mu_1__type_1& a, mu_1__type_1& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = Compare(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    for (int i=0; i<1; i++)
      array[i].MultisetSort();
  }
  void print_statistic()
  {
    for (int i=0; i<1; i++)
      array[i].print_statistic();
  }
  void clear() { for (int i = 0; i < 1; i++) array[i].clear(); };

  void undefine() { for (int i = 0; i < 1; i++) array[i].undefine(); };

  void reset() { for (int i = 0; i < 1; i++) array[i].reset(); };

  void to_state(state *thestate)
  {
    for (int i = 0; i < 1; i++)
      array[i].to_state(thestate);
  };

  void print()
  {
    for (int i = 0; i < 1; i++)
      array[i].print(); };

  void print_diff(state *prevstate)
  {
    for (int i = 0; i < 1; i++)
      array[i].print_diff(prevstate);
  };
};

  void mu_1__type_1::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1__type_1::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1__type_1::set_self( const char *n, int os)
  {
    int i=0;
    name = (char *)n;

if (n) array[i].set_self_ar(n,"CacheLineId_1", i * 16 + os); else array[i].set_self_ar(NULL, NULL, 0); i++;
}
mu_1__type_1::~mu_1__type_1()
{
}
/*** end array declaration ***/
mu_1__type_1 mu_1__type_1_undefined_var;

class mu_1_Cache
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1__type_1 mu_line;
  mu_1_Cache ( const char *n, int os ) { set_self(n,os); };
  mu_1_Cache ( void ) {};

  virtual ~mu_1_Cache(); 
friend int CompareWeight(mu_1_Cache& a, mu_1_Cache& b)
  {
    int w;
    w = CompareWeight(a.mu_line, b.mu_line);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_Cache& a, mu_1_Cache& b)
  {
    int w;
    w = Compare(a.mu_line, b.mu_line);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_line.MultisetSort();
  }
  void print_statistic()
  {
    mu_line.print_statistic();
  }
  void clear() {
    mu_line.clear();
 };
  void undefine() {
    mu_line.undefine();
 };
  void reset() {
    mu_line.reset();
 };
  void print() {
    mu_line.print();
  };
  void print_diff(state *prevstate) {
    mu_line.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_line.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_Cache& operator= (const mu_1_Cache& from) {
    mu_line = from.mu_line;
    return *this;
  };
};

  void mu_1_Cache::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_Cache::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_Cache::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_line.set_self_2(name, ".line", os + 0 ); else mu_line.set_self_2(NULL, NULL, 0);
}

mu_1_Cache::~mu_1_Cache()
{
}

/*** end record declaration ***/
mu_1_Cache mu_1_Cache_undefined_var;

class mu_1_InstructionType: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_InstructionType& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_InstructionType& val)
  {
    if (val.defined())
      return ( s << mu_1_InstructionType::values[ int(val) - 295] );
    else return ( s << "Undefined" );
  };

  mu_1_InstructionType (const char *name, int os): mu__long(295, 300, 3, name, os) {};
  mu_1_InstructionType (void): mu__long(295, 300, 3) {};
  mu_1_InstructionType (int val): mu__long(295, 300, 3, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -295]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -295] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_InstructionType::values[] = {"I_NONE","I_LOAD","I_STORE","I_FLUSH","I_DELETE","I_LOCK",NULL };

/*** end of enum declaration ***/
mu_1_InstructionType mu_1_InstructionType_undefined_var;

class mu_1_InstructionPhase: public mu__long
{
 public:
  inline int operator=(int val) { return value(val); };
  inline int operator=(const mu_1_InstructionPhase& val) { return value(val.value()); };
  static const char *values[];
  friend ostream& operator<< (ostream& s, mu_1_InstructionPhase& val)
  {
    if (val.defined())
      return ( s << mu_1_InstructionPhase::values[ int(val) - 301] );
    else return ( s << "Undefined" );
  };

  mu_1_InstructionPhase (const char *name, int os): mu__long(301, 304, 3, name, os) {};
  mu_1_InstructionPhase (void): mu__long(301, 304, 3) {};
  mu_1_InstructionPhase (int val): mu__long(301, 304, 3, "Parameter or function result.", 0)
  {
     operator=(val);
  };
  const char * Name() { return values[ value() -301]; };
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort() {};
  void print_statistic() {};
  virtual void print()
  {
    if (defined())
      cout << name << ":" << values[ value() -301] << '\n';
    else
      cout << name << ":Undefined\n";
  };
};

const char *mu_1_InstructionPhase::values[] = {"I_START","I_ALLOCATE","I_SETUP","I_CLEANUP",NULL };

/*** end of enum declaration ***/
mu_1_InstructionPhase mu_1_InstructionPhase_undefined_var;

class mu_1_LB
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_MemoryCacheStates mu_cState;
  mu_0_boolean mu_firstTo;
  mu_0_boolean mu_firstEntrySub;
  mu_1_MemoryId mu_memId;
  mu_1_MemoryLineId mu_addrOffset;
  mu_1_LB ( const char *n, int os ) { set_self(n,os); };
  mu_1_LB ( void ) {};

  virtual ~mu_1_LB(); 
friend int CompareWeight(mu_1_LB& a, mu_1_LB& b)
  {
    int w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_firstTo, b.mu_firstTo);
    if (w!=0) return w;
    w = CompareWeight(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = CompareWeight(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
    w = CompareWeight(a.mu_addrOffset, b.mu_addrOffset);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_LB& a, mu_1_LB& b)
  {
    int w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = Compare(a.mu_firstTo, b.mu_firstTo);
    if (w!=0) return w;
    w = Compare(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = Compare(a.mu_memId, b.mu_memId);
    if (w!=0) return w;
    w = Compare(a.mu_addrOffset, b.mu_addrOffset);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_cState.MultisetSort();
    mu_firstTo.MultisetSort();
    mu_firstEntrySub.MultisetSort();
    mu_memId.MultisetSort();
    mu_addrOffset.MultisetSort();
  }
  void print_statistic()
  {
    mu_cState.print_statistic();
    mu_firstTo.print_statistic();
    mu_firstEntrySub.print_statistic();
    mu_memId.print_statistic();
    mu_addrOffset.print_statistic();
  }
  void clear() {
    mu_cState.clear();
    mu_firstTo.clear();
    mu_firstEntrySub.clear();
    mu_memId.clear();
    mu_addrOffset.clear();
 };
  void undefine() {
    mu_cState.undefine();
    mu_firstTo.undefine();
    mu_firstEntrySub.undefine();
    mu_memId.undefine();
    mu_addrOffset.undefine();
 };
  void reset() {
    mu_cState.reset();
    mu_firstTo.reset();
    mu_firstEntrySub.reset();
    mu_memId.reset();
    mu_addrOffset.reset();
 };
  void print() {
    mu_cState.print();
    mu_firstTo.print();
    mu_firstEntrySub.print();
    mu_memId.print();
    mu_addrOffset.print();
  };
  void print_diff(state *prevstate) {
    mu_cState.print_diff(prevstate);
    mu_firstTo.print_diff(prevstate);
    mu_firstEntrySub.print_diff(prevstate);
    mu_memId.print_diff(prevstate);
    mu_addrOffset.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_cState.to_state(thestate);
    mu_firstTo.to_state(thestate);
    mu_firstEntrySub.to_state(thestate);
    mu_memId.to_state(thestate);
    mu_addrOffset.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_LB& operator= (const mu_1_LB& from) {
    mu_cState.value(from.mu_cState.value());
    mu_firstTo.value(from.mu_firstTo.value());
    mu_firstEntrySub.value(from.mu_firstEntrySub.value());
    mu_memId.value(from.mu_memId.value());
    mu_addrOffset.value(from.mu_addrOffset.value());
    return *this;
  };
};

  void mu_1_LB::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_LB::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_LB::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_cState.set_self_2(name, ".cState", os + 0 ); else mu_cState.set_self_2(NULL, NULL, 0);
  if (name) mu_firstTo.set_self_2(name, ".firstTo", os + 8 ); else mu_firstTo.set_self_2(NULL, NULL, 0);
  if (name) mu_firstEntrySub.set_self_2(name, ".firstEntrySub", os + 10 ); else mu_firstEntrySub.set_self_2(NULL, NULL, 0);
  if (name) mu_memId.set_self_2(name, ".memId", os + 12 ); else mu_memId.set_self_2(NULL, NULL, 0);
  if (name) mu_addrOffset.set_self_2(name, ".addrOffset", os + 13 ); else mu_addrOffset.set_self_2(NULL, NULL, 0);
}

mu_1_LB::~mu_1_LB()
{
}

/*** end record declaration ***/
mu_1_LB mu_1_LB_undefined_var;

class mu_1_LC
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_MemoryCacheStates mu_cState;
  mu_1_LC ( const char *n, int os ) { set_self(n,os); };
  mu_1_LC ( void ) {};

  virtual ~mu_1_LC(); 
friend int CompareWeight(mu_1_LC& a, mu_1_LC& b)
  {
    int w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_LC& a, mu_1_LC& b)
  {
    int w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_cState.MultisetSort();
  }
  void print_statistic()
  {
    mu_cState.print_statistic();
  }
  void clear() {
    mu_cState.clear();
 };
  void undefine() {
    mu_cState.undefine();
 };
  void reset() {
    mu_cState.reset();
 };
  void print() {
    mu_cState.print();
  };
  void print_diff(state *prevstate) {
    mu_cState.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_cState.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_LC& operator= (const mu_1_LC& from) {
    mu_cState.value(from.mu_cState.value());
    return *this;
  };
};

  void mu_1_LC::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_LC::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_LC::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_cState.set_self_2(name, ".cState", os + 0 ); else mu_cState.set_self_2(NULL, NULL, 0);
}

mu_1_LC::~mu_1_LC()
{
}

/*** end record declaration ***/
mu_1_LC mu_1_LC_undefined_var;

class mu_1_SubState
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_LB mu_lB;
  mu_1_LC mu_lC;
  mu_1_SubState ( const char *n, int os ) { set_self(n,os); };
  mu_1_SubState ( void ) {};

  virtual ~mu_1_SubState(); 
friend int CompareWeight(mu_1_SubState& a, mu_1_SubState& b)
  {
    int w;
    w = CompareWeight(a.mu_lB, b.mu_lB);
    if (w!=0) return w;
    w = CompareWeight(a.mu_lC, b.mu_lC);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_SubState& a, mu_1_SubState& b)
  {
    int w;
    w = Compare(a.mu_lB, b.mu_lB);
    if (w!=0) return w;
    w = Compare(a.mu_lC, b.mu_lC);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_lB.MultisetSort();
    mu_lC.MultisetSort();
  }
  void print_statistic()
  {
    mu_lB.print_statistic();
    mu_lC.print_statistic();
  }
  void clear() {
    mu_lB.clear();
    mu_lC.clear();
 };
  void undefine() {
    mu_lB.undefine();
    mu_lC.undefine();
 };
  void reset() {
    mu_lB.reset();
    mu_lC.reset();
 };
  void print() {
    mu_lB.print();
    mu_lC.print();
  };
  void print_diff(state *prevstate) {
    mu_lB.print_diff(prevstate);
    mu_lC.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_lB.to_state(thestate);
    mu_lC.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_SubState& operator= (const mu_1_SubState& from) {
    mu_lB = from.mu_lB;
    mu_lC = from.mu_lC;
    return *this;
  };
};

  void mu_1_SubState::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_SubState::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_SubState::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_lB.set_self_2(name, ".lB", os + 0 ); else mu_lB.set_self_2(NULL, NULL, 0);
  if (name) mu_lC.set_self_2(name, ".lC", os + 14 ); else mu_lC.set_self_2(NULL, NULL, 0);
}

mu_1_SubState::~mu_1_SubState()
{
}

/*** end record declaration ***/
mu_1_SubState mu_1_SubState_undefined_var;

class mu_1_L0
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_0_boolean mu_secondEntry;
  mu_1_MemoryCacheStates mu_mState;
  mu_0_boolean mu_co;
  mu_1_L0 ( const char *n, int os ) { set_self(n,os); };
  mu_1_L0 ( void ) {};

  virtual ~mu_1_L0(); 
friend int CompareWeight(mu_1_L0& a, mu_1_L0& b)
  {
    int w;
    w = CompareWeight(a.mu_secondEntry, b.mu_secondEntry);
    if (w!=0) return w;
    w = CompareWeight(a.mu_mState, b.mu_mState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_co, b.mu_co);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_L0& a, mu_1_L0& b)
  {
    int w;
    w = Compare(a.mu_secondEntry, b.mu_secondEntry);
    if (w!=0) return w;
    w = Compare(a.mu_mState, b.mu_mState);
    if (w!=0) return w;
    w = Compare(a.mu_co, b.mu_co);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_secondEntry.MultisetSort();
    mu_mState.MultisetSort();
    mu_co.MultisetSort();
  }
  void print_statistic()
  {
    mu_secondEntry.print_statistic();
    mu_mState.print_statistic();
    mu_co.print_statistic();
  }
  void clear() {
    mu_secondEntry.clear();
    mu_mState.clear();
    mu_co.clear();
 };
  void undefine() {
    mu_secondEntry.undefine();
    mu_mState.undefine();
    mu_co.undefine();
 };
  void reset() {
    mu_secondEntry.reset();
    mu_mState.reset();
    mu_co.reset();
 };
  void print() {
    mu_secondEntry.print();
    mu_mState.print();
    mu_co.print();
  };
  void print_diff(state *prevstate) {
    mu_secondEntry.print_diff(prevstate);
    mu_mState.print_diff(prevstate);
    mu_co.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_secondEntry.to_state(thestate);
    mu_mState.to_state(thestate);
    mu_co.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_L0& operator= (const mu_1_L0& from) {
    mu_secondEntry.value(from.mu_secondEntry.value());
    mu_mState.value(from.mu_mState.value());
    mu_co.value(from.mu_co.value());
    return *this;
  };
};

  void mu_1_L0::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_L0::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_L0::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_secondEntry.set_self_2(name, ".secondEntry", os + 0 ); else mu_secondEntry.set_self_2(NULL, NULL, 0);
  if (name) mu_mState.set_self_2(name, ".mState", os + 2 ); else mu_mState.set_self_2(NULL, NULL, 0);
  if (name) mu_co.set_self_2(name, ".co", os + 10 ); else mu_co.set_self_2(NULL, NULL, 0);
}

mu_1_L0::~mu_1_L0()
{
}

/*** end record declaration ***/
mu_1_L0 mu_1_L0_undefined_var;

class mu_1_L1
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_0_boolean mu_firstEntrySub;
  mu_0_boolean mu_firstLoop;
  mu_1_MemoryCacheStates mu_cState;
  mu_1_L1 ( const char *n, int os ) { set_self(n,os); };
  mu_1_L1 ( void ) {};

  virtual ~mu_1_L1(); 
friend int CompareWeight(mu_1_L1& a, mu_1_L1& b)
  {
    int w;
    w = CompareWeight(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = CompareWeight(a.mu_firstLoop, b.mu_firstLoop);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_L1& a, mu_1_L1& b)
  {
    int w;
    w = Compare(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = Compare(a.mu_firstLoop, b.mu_firstLoop);
    if (w!=0) return w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_firstEntrySub.MultisetSort();
    mu_firstLoop.MultisetSort();
    mu_cState.MultisetSort();
  }
  void print_statistic()
  {
    mu_firstEntrySub.print_statistic();
    mu_firstLoop.print_statistic();
    mu_cState.print_statistic();
  }
  void clear() {
    mu_firstEntrySub.clear();
    mu_firstLoop.clear();
    mu_cState.clear();
 };
  void undefine() {
    mu_firstEntrySub.undefine();
    mu_firstLoop.undefine();
    mu_cState.undefine();
 };
  void reset() {
    mu_firstEntrySub.reset();
    mu_firstLoop.reset();
    mu_cState.reset();
 };
  void print() {
    mu_firstEntrySub.print();
    mu_firstLoop.print();
    mu_cState.print();
  };
  void print_diff(state *prevstate) {
    mu_firstEntrySub.print_diff(prevstate);
    mu_firstLoop.print_diff(prevstate);
    mu_cState.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_firstEntrySub.to_state(thestate);
    mu_firstLoop.to_state(thestate);
    mu_cState.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_L1& operator= (const mu_1_L1& from) {
    mu_firstEntrySub.value(from.mu_firstEntrySub.value());
    mu_firstLoop.value(from.mu_firstLoop.value());
    mu_cState.value(from.mu_cState.value());
    return *this;
  };
};

  void mu_1_L1::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_L1::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_L1::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_firstEntrySub.set_self_2(name, ".firstEntrySub", os + 0 ); else mu_firstEntrySub.set_self_2(NULL, NULL, 0);
  if (name) mu_firstLoop.set_self_2(name, ".firstLoop", os + 2 ); else mu_firstLoop.set_self_2(NULL, NULL, 0);
  if (name) mu_cState.set_self_2(name, ".cState", os + 4 ); else mu_cState.set_self_2(NULL, NULL, 0);
}

mu_1_L1::~mu_1_L1()
{
}

/*** end record declaration ***/
mu_1_L1 mu_1_L1_undefined_var;

class mu_1_L2
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_0_boolean mu_firstEntrySub;
  mu_0_boolean mu_firstLoop;
  mu_1_MemoryCacheStates mu_cState;
  mu_1_ProcId mu_nextId;
  mu_1_L2 ( const char *n, int os ) { set_self(n,os); };
  mu_1_L2 ( void ) {};

  virtual ~mu_1_L2(); 
friend int CompareWeight(mu_1_L2& a, mu_1_L2& b)
  {
    int w;
    w = CompareWeight(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = CompareWeight(a.mu_firstLoop, b.mu_firstLoop);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_nextId, b.mu_nextId);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_L2& a, mu_1_L2& b)
  {
    int w;
    w = Compare(a.mu_firstEntrySub, b.mu_firstEntrySub);
    if (w!=0) return w;
    w = Compare(a.mu_firstLoop, b.mu_firstLoop);
    if (w!=0) return w;
    w = Compare(a.mu_cState, b.mu_cState);
    if (w!=0) return w;
    w = Compare(a.mu_nextId, b.mu_nextId);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_firstEntrySub.MultisetSort();
    mu_firstLoop.MultisetSort();
    mu_cState.MultisetSort();
    mu_nextId.MultisetSort();
  }
  void print_statistic()
  {
    mu_firstEntrySub.print_statistic();
    mu_firstLoop.print_statistic();
    mu_cState.print_statistic();
    mu_nextId.print_statistic();
  }
  void clear() {
    mu_firstEntrySub.clear();
    mu_firstLoop.clear();
    mu_cState.clear();
    mu_nextId.clear();
 };
  void undefine() {
    mu_firstEntrySub.undefine();
    mu_firstLoop.undefine();
    mu_cState.undefine();
    mu_nextId.undefine();
 };
  void reset() {
    mu_firstEntrySub.reset();
    mu_firstLoop.reset();
    mu_cState.reset();
    mu_nextId.reset();
 };
  void print() {
    mu_firstEntrySub.print();
    mu_firstLoop.print();
    mu_cState.print();
    mu_nextId.print();
  };
  void print_diff(state *prevstate) {
    mu_firstEntrySub.print_diff(prevstate);
    mu_firstLoop.print_diff(prevstate);
    mu_cState.print_diff(prevstate);
    mu_nextId.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_firstEntrySub.to_state(thestate);
    mu_firstLoop.to_state(thestate);
    mu_cState.to_state(thestate);
    mu_nextId.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_L2& operator= (const mu_1_L2& from) {
    mu_firstEntrySub.value(from.mu_firstEntrySub.value());
    mu_firstLoop.value(from.mu_firstLoop.value());
    mu_cState.value(from.mu_cState.value());
    mu_nextId.value(from.mu_nextId.value());
    return *this;
  };
};

  void mu_1_L2::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_L2::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_L2::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_firstEntrySub.set_self_2(name, ".firstEntrySub", os + 0 ); else mu_firstEntrySub.set_self_2(NULL, NULL, 0);
  if (name) mu_firstLoop.set_self_2(name, ".firstLoop", os + 2 ); else mu_firstLoop.set_self_2(NULL, NULL, 0);
  if (name) mu_cState.set_self_2(name, ".cState", os + 4 ); else mu_cState.set_self_2(NULL, NULL, 0);
  if (name) mu_nextId.set_self_2(name, ".nextId", os + 12 ); else mu_nextId.set_self_2(NULL, NULL, 0);
}

mu_1_L2::~mu_1_L2()
{
}

/*** end record declaration ***/
mu_1_L2 mu_1_L2_undefined_var;

class mu_1_ToState
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_L0 mu_l0;
  mu_1_L1 mu_l1;
  mu_1_L2 mu_l2;
  mu_1_ToState ( const char *n, int os ) { set_self(n,os); };
  mu_1_ToState ( void ) {};

  virtual ~mu_1_ToState(); 
friend int CompareWeight(mu_1_ToState& a, mu_1_ToState& b)
  {
    int w;
    w = CompareWeight(a.mu_l0, b.mu_l0);
    if (w!=0) return w;
    w = CompareWeight(a.mu_l1, b.mu_l1);
    if (w!=0) return w;
    w = CompareWeight(a.mu_l2, b.mu_l2);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_ToState& a, mu_1_ToState& b)
  {
    int w;
    w = Compare(a.mu_l0, b.mu_l0);
    if (w!=0) return w;
    w = Compare(a.mu_l1, b.mu_l1);
    if (w!=0) return w;
    w = Compare(a.mu_l2, b.mu_l2);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_l0.MultisetSort();
    mu_l1.MultisetSort();
    mu_l2.MultisetSort();
  }
  void print_statistic()
  {
    mu_l0.print_statistic();
    mu_l1.print_statistic();
    mu_l2.print_statistic();
  }
  void clear() {
    mu_l0.clear();
    mu_l1.clear();
    mu_l2.clear();
 };
  void undefine() {
    mu_l0.undefine();
    mu_l1.undefine();
    mu_l2.undefine();
 };
  void reset() {
    mu_l0.reset();
    mu_l1.reset();
    mu_l2.reset();
 };
  void print() {
    mu_l0.print();
    mu_l1.print();
    mu_l2.print();
  };
  void print_diff(state *prevstate) {
    mu_l0.print_diff(prevstate);
    mu_l1.print_diff(prevstate);
    mu_l2.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_l0.to_state(thestate);
    mu_l1.to_state(thestate);
    mu_l2.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_ToState& operator= (const mu_1_ToState& from) {
    mu_l0 = from.mu_l0;
    mu_l1 = from.mu_l1;
    mu_l2 = from.mu_l2;
    return *this;
  };
};

  void mu_1_ToState::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_ToState::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_ToState::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_l0.set_self_2(name, ".l0", os + 0 ); else mu_l0.set_self_2(NULL, NULL, 0);
  if (name) mu_l1.set_self_2(name, ".l1", os + 12 ); else mu_l1.set_self_2(NULL, NULL, 0);
  if (name) mu_l2.set_self_2(name, ".l2", os + 24 ); else mu_l2.set_self_2(NULL, NULL, 0);
}

mu_1_ToState::~mu_1_ToState()
{
}

/*** end record declaration ***/
mu_1_ToState mu_1_ToState_undefined_var;

class mu_1_ExecState
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_InstructionType mu_insType;
  mu_1_InstructionPhase mu_insPhase;
  mu_1_CacheLineId mu_cTPtr;
  mu_1_TransactStatus mu_tStat;
  mu_1_FetchOptions mu_fetchOption;
  mu_1_Data mu_data;
  mu_1_SubState mu_subState;
  mu_1_ToState mu_toState;
  mu_1_ExecState ( const char *n, int os ) { set_self(n,os); };
  mu_1_ExecState ( void ) {};

  virtual ~mu_1_ExecState(); 
friend int CompareWeight(mu_1_ExecState& a, mu_1_ExecState& b)
  {
    int w;
    w = CompareWeight(a.mu_insType, b.mu_insType);
    if (w!=0) return w;
    w = CompareWeight(a.mu_insPhase, b.mu_insPhase);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cTPtr, b.mu_cTPtr);
    if (w!=0) return w;
    w = CompareWeight(a.mu_tStat, b.mu_tStat);
    if (w!=0) return w;
    w = CompareWeight(a.mu_fetchOption, b.mu_fetchOption);
    if (w!=0) return w;
    w = CompareWeight(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = CompareWeight(a.mu_subState, b.mu_subState);
    if (w!=0) return w;
    w = CompareWeight(a.mu_toState, b.mu_toState);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_ExecState& a, mu_1_ExecState& b)
  {
    int w;
    w = Compare(a.mu_insType, b.mu_insType);
    if (w!=0) return w;
    w = Compare(a.mu_insPhase, b.mu_insPhase);
    if (w!=0) return w;
    w = Compare(a.mu_cTPtr, b.mu_cTPtr);
    if (w!=0) return w;
    w = Compare(a.mu_tStat, b.mu_tStat);
    if (w!=0) return w;
    w = Compare(a.mu_fetchOption, b.mu_fetchOption);
    if (w!=0) return w;
    w = Compare(a.mu_data, b.mu_data);
    if (w!=0) return w;
    w = Compare(a.mu_subState, b.mu_subState);
    if (w!=0) return w;
    w = Compare(a.mu_toState, b.mu_toState);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_insType.MultisetSort();
    mu_insPhase.MultisetSort();
    mu_cTPtr.MultisetSort();
    mu_tStat.MultisetSort();
    mu_fetchOption.MultisetSort();
    mu_data.MultisetSort();
    mu_subState.MultisetSort();
    mu_toState.MultisetSort();
  }
  void print_statistic()
  {
    mu_insType.print_statistic();
    mu_insPhase.print_statistic();
    mu_cTPtr.print_statistic();
    mu_tStat.print_statistic();
    mu_fetchOption.print_statistic();
    mu_data.print_statistic();
    mu_subState.print_statistic();
    mu_toState.print_statistic();
  }
  void clear() {
    mu_insType.clear();
    mu_insPhase.clear();
    mu_cTPtr.clear();
    mu_tStat.clear();
    mu_fetchOption.clear();
    mu_data.clear();
    mu_subState.clear();
    mu_toState.clear();
 };
  void undefine() {
    mu_insType.undefine();
    mu_insPhase.undefine();
    mu_cTPtr.undefine();
    mu_tStat.undefine();
    mu_fetchOption.undefine();
    mu_data.undefine();
    mu_subState.undefine();
    mu_toState.undefine();
 };
  void reset() {
    mu_insType.reset();
    mu_insPhase.reset();
    mu_cTPtr.reset();
    mu_tStat.reset();
    mu_fetchOption.reset();
    mu_data.reset();
    mu_subState.reset();
    mu_toState.reset();
 };
  void print() {
    mu_insType.print();
    mu_insPhase.print();
    mu_cTPtr.print();
    mu_tStat.print();
    mu_fetchOption.print();
    mu_data.print();
    mu_subState.print();
    mu_toState.print();
  };
  void print_diff(state *prevstate) {
    mu_insType.print_diff(prevstate);
    mu_insPhase.print_diff(prevstate);
    mu_cTPtr.print_diff(prevstate);
    mu_tStat.print_diff(prevstate);
    mu_fetchOption.print_diff(prevstate);
    mu_data.print_diff(prevstate);
    mu_subState.print_diff(prevstate);
    mu_toState.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_insType.to_state(thestate);
    mu_insPhase.to_state(thestate);
    mu_cTPtr.to_state(thestate);
    mu_tStat.to_state(thestate);
    mu_fetchOption.to_state(thestate);
    mu_data.to_state(thestate);
    mu_subState.to_state(thestate);
    mu_toState.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_ExecState& operator= (const mu_1_ExecState& from) {
    mu_insType.value(from.mu_insType.value());
    mu_insPhase.value(from.mu_insPhase.value());
    mu_cTPtr.value(from.mu_cTPtr.value());
    mu_tStat.value(from.mu_tStat.value());
    mu_fetchOption.value(from.mu_fetchOption.value());
    mu_data.value(from.mu_data.value());
    mu_subState = from.mu_subState;
    mu_toState = from.mu_toState;
    return *this;
  };
};

  void mu_1_ExecState::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_ExecState::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_ExecState::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_insType.set_self_2(name, ".insType", os + 0 ); else mu_insType.set_self_2(NULL, NULL, 0);
  if (name) mu_insPhase.set_self_2(name, ".insPhase", os + 3 ); else mu_insPhase.set_self_2(NULL, NULL, 0);
  if (name) mu_cTPtr.set_self_2(name, ".cTPtr", os + 6 ); else mu_cTPtr.set_self_2(NULL, NULL, 0);
  if (name) mu_tStat.set_self_2(name, ".tStat", os + 7 ); else mu_tStat.set_self_2(NULL, NULL, 0);
  if (name) mu_fetchOption.set_self_2(name, ".fetchOption", os + 12 ); else mu_fetchOption.set_self_2(NULL, NULL, 0);
  if (name) mu_data.set_self_2(name, ".data", os + 14 ); else mu_data.set_self_2(NULL, NULL, 0);
  if (name) mu_subState.set_self_2(name, ".subState", os + 15 ); else mu_subState.set_self_2(NULL, NULL, 0);
  if (name) mu_toState.set_self_2(name, ".toState", os + 37 ); else mu_toState.set_self_2(NULL, NULL, 0);
}

mu_1_ExecState::~mu_1_ExecState()
{
}

/*** end record declaration ***/
mu_1_ExecState mu_1_ExecState_undefined_var;

class mu_1_ExecUnit
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_ExecState mu_state;
  mu_1_ReqPacket mu_reqPacket;
  mu_1_ResPacket mu_resPacket;
  mu_1_ExecUnit ( const char *n, int os ) { set_self(n,os); };
  mu_1_ExecUnit ( void ) {};

  virtual ~mu_1_ExecUnit(); 
friend int CompareWeight(mu_1_ExecUnit& a, mu_1_ExecUnit& b)
  {
    int w;
    w = CompareWeight(a.mu_state, b.mu_state);
    if (w!=0) return w;
    w = CompareWeight(a.mu_reqPacket, b.mu_reqPacket);
    if (w!=0) return w;
    w = CompareWeight(a.mu_resPacket, b.mu_resPacket);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_ExecUnit& a, mu_1_ExecUnit& b)
  {
    int w;
    w = Compare(a.mu_state, b.mu_state);
    if (w!=0) return w;
    w = Compare(a.mu_reqPacket, b.mu_reqPacket);
    if (w!=0) return w;
    w = Compare(a.mu_resPacket, b.mu_resPacket);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_state.MultisetSort();
    mu_reqPacket.MultisetSort();
    mu_resPacket.MultisetSort();
  }
  void print_statistic()
  {
    mu_state.print_statistic();
    mu_reqPacket.print_statistic();
    mu_resPacket.print_statistic();
  }
  void clear() {
    mu_state.clear();
    mu_reqPacket.clear();
    mu_resPacket.clear();
 };
  void undefine() {
    mu_state.undefine();
    mu_reqPacket.undefine();
    mu_resPacket.undefine();
 };
  void reset() {
    mu_state.reset();
    mu_reqPacket.reset();
    mu_resPacket.reset();
 };
  void print() {
    mu_state.print();
    mu_reqPacket.print();
    mu_resPacket.print();
  };
  void print_diff(state *prevstate) {
    mu_state.print_diff(prevstate);
    mu_reqPacket.print_diff(prevstate);
    mu_resPacket.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_state.to_state(thestate);
    mu_reqPacket.to_state(thestate);
    mu_resPacket.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_ExecUnit& operator= (const mu_1_ExecUnit& from) {
    mu_state = from.mu_state;
    mu_reqPacket = from.mu_reqPacket;
    mu_resPacket = from.mu_resPacket;
    return *this;
  };
};

  void mu_1_ExecUnit::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_ExecUnit::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_ExecUnit::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_state.set_self_2(name, ".state", os + 0 ); else mu_state.set_self_2(NULL, NULL, 0);
  if (name) mu_reqPacket.set_self_2(name, ".reqPacket", os + 75 ); else mu_reqPacket.set_self_2(NULL, NULL, 0);
  if (name) mu_resPacket.set_self_2(name, ".resPacket", os + 97 ); else mu_resPacket.set_self_2(NULL, NULL, 0);
}

mu_1_ExecUnit::~mu_1_ExecUnit()
{
}

/*** end record declaration ***/
mu_1_ExecUnit mu_1_ExecUnit_undefined_var;

class mu_1_Proc
{
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  void set_self(const char *n, int os);
  mu_1_ExecUnit mu_exec;
  mu_1_Cache mu_cache;
  mu_1_Proc ( const char *n, int os ) { set_self(n,os); };
  mu_1_Proc ( void ) {};

  virtual ~mu_1_Proc(); 
friend int CompareWeight(mu_1_Proc& a, mu_1_Proc& b)
  {
    int w;
    w = CompareWeight(a.mu_exec, b.mu_exec);
    if (w!=0) return w;
    w = CompareWeight(a.mu_cache, b.mu_cache);
    if (w!=0) return w;
  return 0;
}
friend int Compare(mu_1_Proc& a, mu_1_Proc& b)
  {
    int w;
    w = Compare(a.mu_exec, b.mu_exec);
    if (w!=0) return w;
    w = Compare(a.mu_cache, b.mu_cache);
    if (w!=0) return w;
  return 0;
}
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    mu_exec.MultisetSort();
    mu_cache.MultisetSort();
  }
  void print_statistic()
  {
    mu_exec.print_statistic();
    mu_cache.print_statistic();
  }
  void clear() {
    mu_exec.clear();
    mu_cache.clear();
 };
  void undefine() {
    mu_exec.undefine();
    mu_cache.undefine();
 };
  void reset() {
    mu_exec.reset();
    mu_cache.reset();
 };
  void print() {
    mu_exec.print();
    mu_cache.print();
  };
  void print_diff(state *prevstate) {
    mu_exec.print_diff(prevstate);
    mu_cache.print_diff(prevstate);
  };
  void to_state(state *thestate) {
    mu_exec.to_state(thestate);
    mu_cache.to_state(thestate);
  };
virtual bool isundefined() { Error.Error("Checking undefinedness of a non-base type"); return TRUE;}
virtual bool ismember() { Error.Error("Checking membership for a non-base type"); return TRUE;}
  mu_1_Proc& operator= (const mu_1_Proc& from) {
    mu_exec = from.mu_exec;
    mu_cache = from.mu_cache;
    return *this;
  };
};

  void mu_1_Proc::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1_Proc::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1_Proc::set_self(const char *n, int os)
{
  name = (char *)n;

  if (name) mu_exec.set_self_2(name, ".exec", os + 0 ); else mu_exec.set_self_2(NULL, NULL, 0);
  if (name) mu_cache.set_self_2(name, ".cache", os + 116 ); else mu_cache.set_self_2(NULL, NULL, 0);
}

mu_1_Proc::~mu_1_Proc()
{
}

/*** end record declaration ***/
mu_1_Proc mu_1_Proc_undefined_var;

class mu_1__type_2
{
 public:
  mu_1_Proc array[ 2 ];
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self( const char *n, int os);
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  mu_1__type_2 (const char *n, int os) { set_self(n, os); };
  mu_1__type_2 ( void ) {};
  virtual ~mu_1__type_2 ();
  mu_1_Proc& operator[] (int index) /* const */
  {
#ifndef NO_RUN_TIME_CHECKING
    if ( ( index >= 1 ) && ( index <= 2 ) )
      return array[ index - 1 ];
    else
      {
	if (index==UNDEFVAL) 
	  Error.Error("Indexing to %s using an undefined value.", name);
	else
	  Error.Error("Funny index value %d for %s: ProcId is internally represented from 2 to 1.\nInternal Error in Type checking.",index, name);
	return array[0];
      }
#else
    return array[ index - 1 ];
#endif
  };
  mu_1__type_2& operator= (const mu_1__type_2& from)
  {
    for (int i = 0; i < 2; i++)
      array[i] = from.array[i];
    return *this;
  }

friend int CompareWeight(mu_1__type_2& a, mu_1__type_2& b)
  {
    return 0;
  }
friend int Compare(mu_1__type_2& a, mu_1__type_2& b)
  {
    int w;
    for (int i=0; i<2; i++) {
      w = Compare(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    for (int i=0; i<2; i++)
      array[i].MultisetSort();
  }
  void print_statistic()
  {
    for (int i=0; i<2; i++)
      array[i].print_statistic();
  }
  void clear() { for (int i = 0; i < 2; i++) array[i].clear(); };

  void undefine() { for (int i = 0; i < 2; i++) array[i].undefine(); };

  void reset() { for (int i = 0; i < 2; i++) array[i].reset(); };

  void to_state(state *thestate)
  {
    for (int i = 0; i < 2; i++)
      array[i].to_state(thestate);
  };

  void print()
  {
    for (int i = 0; i < 2; i++)
      array[i].print(); };

  void print_diff(state *prevstate)
  {
    for (int i = 0; i < 2; i++)
      array[i].print_diff(prevstate);
  };
};

  void mu_1__type_2::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1__type_2::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1__type_2::set_self( const char *n, int os)
  {
    int i=0;
    name = (char *)n;

if (n) array[i].set_self_ar(n,"ProcId_1", i * 132 + os); else array[i].set_self_ar(NULL, NULL, 0); i++;
if (n) array[i].set_self_ar(n,"ProcId_2", i * 132 + os); else array[i].set_self_ar(NULL, NULL, 0); i++;
}
mu_1__type_2::~mu_1__type_2()
{
}
/*** end array declaration ***/
mu_1__type_2 mu_1__type_2_undefined_var;

class mu_1__type_3
{
 public:
  mu_1_Memory array[ 1 ];
 public:
  char *name;
  char longname[BUFFER_SIZE/4];
  void set_self( const char *n, int os);
  void set_self_2( const char *n, const char *n2, int os);
  void set_self_ar( const char *n, const char *n2, int os);
  mu_1__type_3 (const char *n, int os) { set_self(n, os); };
  mu_1__type_3 ( void ) {};
  virtual ~mu_1__type_3 ();
  mu_1_Memory& operator[] (int index) /* const */
  {
#ifndef NO_RUN_TIME_CHECKING
    if ( ( index >= 3 ) && ( index <= 3 ) )
      return array[ index - 3 ];
    else
      {
	if (index==UNDEFVAL) 
	  Error.Error("Indexing to %s using an undefined value.", name);
	else
	  Error.Error("Funny index value %d for %s: MemoryId is internally represented from 3 to 3.\nInternal Error in Type checking.",index, name);
	return array[0];
      }
#else
    return array[ index - 3 ];
#endif
  };
  mu_1__type_3& operator= (const mu_1__type_3& from)
  {
      array[0] = from.array[0];
    return *this;
  }

friend int CompareWeight(mu_1__type_3& a, mu_1__type_3& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = CompareWeight(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
friend int Compare(mu_1__type_3& a, mu_1__type_3& b)
  {
    int w;
    for (int i=0; i<1; i++) {
      w = Compare(a.array[i], b.array[i]);
      if (w!=0) return w;
    }
    return 0;
  }
  virtual void Permute(PermSet& Perm, int i);
  virtual void SimpleCanonicalize(PermSet& Perm);
  virtual void Canonicalize(PermSet& Perm);
  virtual void SimpleLimit(PermSet& Perm);
  virtual void ArrayLimit(PermSet& Perm);
  virtual void Limit(PermSet& Perm);
  virtual void MultisetLimit(PermSet& Perm);
  virtual void MultisetSort()
  {
    for (int i=0; i<1; i++)
      array[i].MultisetSort();
  }
  void print_statistic()
  {
    for (int i=0; i<1; i++)
      array[i].print_statistic();
  }
  void clear() { for (int i = 0; i < 1; i++) array[i].clear(); };

  void undefine() { for (int i = 0; i < 1; i++) array[i].undefine(); };

  void reset() { for (int i = 0; i < 1; i++) array[i].reset(); };

  void to_state(state *thestate)
  {
    for (int i = 0; i < 1; i++)
      array[i].to_state(thestate);
  };

  void print()
  {
    for (int i = 0; i < 1; i++)
      array[i].print(); };

  void print_diff(state *prevstate)
  {
    for (int i = 0; i < 1; i++)
      array[i].print_diff(prevstate);
  };
};

  void mu_1__type_3::set_self_ar( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    int l1 = strlen(n1), l2 = strlen(n2);
    strcpy( longname, n1 );
    longname[l1] = '[';
    strcpy( longname+l1+1, n2 );
    longname[l1+l2+1] = ']';
    longname[l1+l2+2] = 0;
    set_self( longname, os );
  };
  void mu_1__type_3::set_self_2( const char *n1, const char *n2, int os ) {
    if (n1 == NULL) {set_self(NULL, 0); return;}
    strcpy( longname, n1 );
    strcat( longname, n2 );
    set_self( longname, os );
  };
void mu_1__type_3::set_self( const char *n, int os)
  {
    int i=0;
    name = (char *)n;

if (n) array[i].set_self_ar(n,"MemoryId_1", i * 11 + os); else array[i].set_self_ar(NULL, NULL, 0); i++;
}
mu_1__type_3::~mu_1__type_3()
{
}
/*** end array declaration ***/
mu_1__type_3 mu_1__type_3_undefined_var;

const int mu_NumProcs = 2;
const int mu_CacheSize = 1;
const int mu_NumMemories = 1;
const int mu_MemorySize = 1;
const int mu_NumDataValues = 1;
const int mu_EN_LOAD = 0;
const int mu_EN_DELETE = 0;
const int mu_EN_STORE = 1;
const int mu_EN_FLUSH = 1;
const int mu_FO_FETCH = 0;
const int mu_FO_LOAD = 1;
const int mu_FO_STORE = 0;
const int mu_COP_DIRTY = 0;
const int mu_COP_FRESH = 1;
const int mu_COP_MODS = 1;
const int mu_POP_DIRTY = 0;
const int mu_POP_FRESH = 1;
const int mu_POP_MODS = 1;
const int mu_MOP_FRESH = 1;
const int mu_COP_CLEAN = 0;
const int mu_POP_CLEAN = 0;
const int mu_POP_PAIR = 0;
const int mu_POP_QOLB = 0;
const int mu_POP_WASH = 0;
const int mu_POP_CLEANSE = 0;
const int mu_POP_ROBUST = 0;
const int mu_ProcId_1 = 1;
const int mu_ProcId_2 = 2;
const int mu_MemoryId_1 = 3;
const int mu_MemoryLineId_1 = 4;
const int mu_CacheLineId_1 = 5;
const int mu_Data_1 = 6;
const int mu_SC_MREAD = 7;
const int mu_SC_MWRITE64 = 8;
const int mu_SC_CREAD = 9;
const int mu_SC_RESP00 = 10;
const int mu_SC_RESP64 = 11;
const int mu_MC_PASS_HEAD = 12;
const int mu_MC_CACHE_FRESH = 13;
const int mu_MC_CACHE_CLEAN = 14;
const int mu_MC_CACHE_DIRTY = 15;
const int mu_MC_LOCK_CLEAR = 16;
const int mu_MC_LOCK_SET = 17;
const int mu_MC_ATTACH_TO_GONE = 18;
const int mu_MC_ATTACH_TO_LIST = 19;
const int mu_MC_LIST_TO_GONE = 20;
const int mu_MC_FRESH_TO_HOME = 21;
const int mu_MC_LIST_TO_HOME = 22;
const int mu_MC_LIST_TO_FRESH = 23;
const int mu_MC_WASH_TO_FRESH = 24;
const int mu_CC_LOCK_CLEAR = 25;
const int mu_CC_PEND_VALID = 26;
const int mu_CC_FRESH_INVALID = 27;
const int mu_CC_NEXT_SSAVE = 28;
const int mu_CC_PREV_VMID = 29;
const int mu_CC_PREV_VTAIL = 30;
const int mu_CC_VALID_INVALID = 31;
const int mu_CC_TAIL_INVALID = 32;
const int mu_CC_NEXT_VMID = 33;
const int mu_CC_NEXT_FHEAD = 34;
const int mu_CC_NEXT_CHEAD = 35;
const int mu_CC_NEXT_DHEAD = 36;
const int mu_CC_HEADD_TO_STALE = 37;
const int mu_CC_HEADV_TO_STALE = 38;
const int mu_CC_TAILD_TO_STALE = 39;
const int mu_CC_TAILV_TO_STALE = 40;
const int mu_CC_PREV_IMID = 41;
const int mu_CC_PREV_DTAIL = 42;
const int mu_CC_PREV_STAIL = 43;
const int mu_CC_PREV_ITAIL = 44;
const int mu_CC_NEXT_IMID = 45;
const int mu_CC_NEXT_VHEAD = 46;
const int mu_CC_NEXT_SHEAD = 47;
const int mu_CC_NEXT_IHEAD = 48;
const int mu_CC_LOCK_SET = 49;
const int mu_CC_COPY_VALID = 50;
const int mu_CC_COPY_STALE = 51;
const int mu_CC_COPY_QOLB = 52;
const int mu_CC_HEADE_TO_DIRTY = 53;
const int mu_CC_TAILE_TO_DIRTY = 54;
const int mu_CC_HEADE_TO_STALE0 = 55;
const int mu_CC_HEADE_TO_STALE1 = 56;
const int mu_CC_TAILE_TO_STALE0 = 57;
const int mu_CC_TAILE_TO_STALE1 = 58;
const int mu_CC_HEADU_TO_NEED0 = 59;
const int mu_CC_HEADU_TO_NEED1 = 60;
const int mu_CC_TAILU_TO_NEED0 = 61;
const int mu_CC_TAILU_TO_NEED1 = 62;
const int mu_CC_NEXT_EHEAD = 63;
const int mu_CC_NEXT_NHEAD = 64;
const int mu_CC_PREV_ETAIL = 65;
const int mu_CC_PREV_NTAIL = 66;
const int mu_CC_PREVI_TO_USED = 67;
const int mu_CC_PREVI_TO_NEED = 68;
const int mu_CC_TAILI_TO_USED = 69;
const int mu_CC_TAILI_TO_NEED = 70;
const int mu_RESP_NORMAL = 71;
const int mu_RESP_ADVICE = 72;
const int mu_RESP_GONE = 73;
const int mu_RESP_LOCKED = 74;
const int mu_RESP_CONFLICT = 75;
const int mu_RESP_DATA = 76;
const int mu_RESP_TYPE = 77;
const int mu_RESP_ADDRESS = 78;
const int mu_MS_HOME = 79;
const int mu_MS_FRESH = 80;
const int mu_MS_GONE = 81;
const int mu_MS_WASH = 82;
const int mu_CS_INVALID = 83;
const int mu_CS_OD_RETN_IN = 84;
const int mu_CS_OD_spin_IN = 85;
const int mu_CS_QUEUED_FRESH = 86;
const int mu_CS_ONLY_DIRTY = 87;
const int mu_CS_QUEUED_DIRTY = 88;
const int mu_CS_HEAD_DIRTY = 89;
const int mu_CS_QUEUED_CLEAN = 90;
const int mu_CS_QUEUED_MODS = 91;
const int mu_CS_PENDING = 92;
const int mu_CS_QUEUED_JUNK = 93;
const int mu_CS_MV_forw_MV = 94;
const int mu_CS_MV_back_IN = 95;
const int mu_CS_MID_VALID = 96;
const int mu_CS_MID_COPY = 97;
const int mu_CS_ONLYQ_DIRTY = 98;
const int mu_CS_HD_INVAL_OD = 99;
const int mu_CS_MI_forw_MI = 100;
const int mu_CS_MI_back_IN = 101;
const int mu_CS_HEAD_IDLE = 102;
const int mu_CS_MID_IDLE = 103;
const int mu_CS_TAIL_VALID = 104;
const int mu_CS_TAIL_COPY = 105;
const int mu_CS_OF_retn_IN = 106;
const int mu_CS_QUEUED_HOME = 107;
const int mu_CS_HX_FORW_HX = 108;
const int mu_CS_HX_FORW_OX = 109;
const int mu_CS_ONLY_FRESH = 110;
const int mu_CS_OF_MODS_OD = 111;
const int mu_CS_HX_INVAL_OX = 112;
const int mu_CS_HEAD_FRESH = 113;
const int mu_CS_HF_MODS_HD = 114;
const int mu_CS_TO_INVALID = 115;
const int mu_CS_TV_back_IN = 116;
const int mu_CS_QF_FLUSH_IN = 117;
const int mu_CS_LOCAL_CLEAN = 118;
const int mu_CS_HW_WASH_HF = 119;
const int mu_CS_ONLYP_DIRTY = 120;
const int mu_CS_HEAD_STALE0 = 121;
const int mu_CS_HEAD_STALE1 = 122;
const int mu_CS_HX_retn_IN = 123;
const int mu_CS_HEAD_VALID = 124;
const int mu_CS_LOCAL_DIRTY = 125;
const int mu_CS_H0_PEND_HX = 126;
const int mu_CS_H1_PEND_HX = 127;
const int mu_CS_HX_PEND_HX = 128;
const int mu_CS_OC_retn_IN = 129;
const int mu_CS_HEAD_CLEAN = 130;
const int mu_CS_ONLY_CLEAN = 131;
const int mu_CS_HX_XXXX_OD = 132;
const int mu_CS_TS0_Move_TE = 133;
const int mu_CS_TS1_Move_TE = 134;
const int mu_CS_TS_copy_TV = 135;
const int mu_CS_TV_mark_TS = 136;
const int mu_CS_HEAD_WASH = 137;
const int mu_CS_TX_XXXX_OD = 138;
const int mu_CS_TV_mark_TE = 139;
const int mu_CS_TD_back_IN = 140;
const int mu_CS_TS_back_IN = 141;
const int mu_CS_TE_back_IN = 142;
const int mu_CS_TAIL_DIRTY = 143;
const int mu_CS_TAIL_EXCL = 144;
const int mu_CS_TD_mark_TE = 145;
const int mu_CS_TAIL_IDLE = 146;
const int mu_CS_TI_back_IN = 147;
const int mu_CS_TAIL_STALE0 = 148;
const int mu_CS_TAIL_STALE1 = 149;
const int mu_CS_HV_MARK_HE = 150;
const int mu_CS_HEAD_EXCL = 151;
const int mu_CS_HD_MARK_HE = 152;
const int mu_CS_TN_back_IN = 153;
const int mu_CS_TN_send_TS = 154;
const int mu_CS_TN_send_TI = 155;
const int mu_CS_OD_CLEAN_OC = 156;
const int mu_CS_ONLY_USED = 157;
const int mu_CS_TAIL_NEED = 158;
const int mu_CS_HS0_MOVE_HE = 159;
const int mu_CS_HS1_MOVE_HE = 160;
const int mu_CS_HS_COPY_HV = 161;
const int mu_CS_HV_MARK_HS = 162;
const int mu_CS_HD_CLEAN_HC = 163;
const int mu_CS_HEAD_NEED = 164;
const int mu_CS_SAVE_STALE = 165;
const int mu_CS_SS_next_IN = 166;
const int mu_CS_HN_SEND_HS = 167;
const int mu_CS_HN_SEND_HI = 168;
const int mu_CS_HD_WASH_HF = 169;
const int mu_CS_TAIL_USED = 170;
const int mu_CS_HS0_MOVE_HI = 171;
const int mu_CS_HS1_MOVE_HI = 172;
const int mu_CS_TS0_Move_TI = 173;
const int mu_CS_TS1_Move_TI = 174;
const int mu_CS_HEAD_USED = 175;
const int mu_CI_HEAD_DIRTY = 176;
const int mu_CI_HEAD_CLEAN = 177;
const int mu_CI_HEAD_WASH = 178;
const int mu_CI_HEAD_MODS = 179;
const int mu_CI_HEADQ_DIRTY = 180;
const int mu_CI_HEADQ_EXCL = 181;
const int mu_CI_HD_WASH_HF = 182;
const int mu_CI_HW_WASH_HF = 183;
const int mu_CI_QUEUED_CLEAN = 184;
const int mu_CI_QUEUED_FRESH = 185;
const int mu_CI_QUEUED_DIRTY = 186;
const int mu_CI_ONLY_EXCL = 187;
const int mu_CI_HEAD_EXCL = 188;
const int mu_CI_TAIL_EXCL = 189;
const int mu_CI_QD_MODS_OU = 190;
const int mu_CI_HD_MODS_OU = 191;
const int mu_CI_HD_FLUSH_IN = 192;
const int mu_CI_HC_FLUSH_IN = 193;
const int mu_CI_LD_FLUSH_IN = 194;
const int mu_CI_OD_PURGE_IN = 195;
const int mu_CI_HN_PURGE_IN = 196;
const int mu_CI_HE_PURGE_IN = 197;
const int mu_CI_HD_PURGE_IN = 198;
const int mu_CI_LD_CLEAN_LC = 199;
const int mu_CI_OD_CLEAN_OC = 200;
const int mu_CI_HD_CLEAN_HC = 201;
const int mu_CI_HN_CLEAN_OC = 202;
const int mu_CI_HE_CLEAN_OC = 203;
const int mu_CI_HD_MODS_HE = 204;
const int mu_CI_HD_MODS_HU = 205;
const int mu_CI_TD_MODS_TE = 206;
const int mu_CI_TD_MODS_TU = 207;
const int mu_CI_HN_DEQOLB_HS = 208;
const int mu_CI_TN_DEQOLB_TS = 209;
const int mu_CI_HN_REQOLB_HI = 210;
const int mu_CI_TN_REQOLB_TI = 211;
const int mu_CI_HI_DELETE_IN = 212;
const int mu_CI_MI_DELETE_IN = 213;
const int mu_CI_TI_DELETE_IN = 214;
const int mu_CI_CHECK_HOME = 215;
const int mu_CI_HF_FLUSH_IN = 216;
const int mu_CI_QF_FLUSH_IN = 217;
const int mu_CI_QD_FLUSH_IN = 218;
const int mu_CI_OD_FLUSH_IN = 219;
const int mu_CI_OC_FLUSH_IN = 220;
const int mu_CI_OF_FLUSH_IN = 221;
const int mu_CI_HN_FLUSH_IN = 222;
const int mu_CI_HE_FLUSH_IN = 223;
const int mu_CI_WRITE_CHECK = 224;
const int mu_CI_WC_DONE_IN = 225;
const int mu_CI_READ_FRESH = 226;
const int mu_CI_ONLY_CLEAN = 227;
const int mu_CI_ONLY_DIRTY = 228;
const int mu_NORM_NONE = 229;
const int mu_NORM_DATA = 230;
const int mu_NORM_NULL = 231;
const int mu_NORM_SKIP = 232;
const int mu_FULL_NONE = 233;
const int mu_FULL_DATA = 234;
const int mu_FULL_NULL = 235;
const int mu_HUGE_TAGS = 236;
const int mu_LOCK_DATA = 237;
const int mu_MISS_MORE = 238;
const int mu_MISS_NONE = 239;
const int mu_CT_ONLY_DIRTY = 240;
const int mu_CT_HEAD_DIRTY = 241;
const int mu_CT_MID_VALID = 242;
const int mu_CT_HEAD_IDLE = 243;
const int mu_CT_ONLY_FRESH = 244;
const int mu_CT_HEAD_FRESH = 245;
const int mu_CT_ONLYP_DIRTY = 246;
const int mu_CT_HEAD_RETN = 247;
const int mu_CT_HEAD_CLEAN = 248;
const int mu_CT_HEAD_WASH = 249;
const int mu_CT_TAIL_EXCL = 250;
const int mu_CT_HEAD_EXCL = 251;
const int mu_CT_ONLY_USED = 252;
const int mu_CT_HEAD_NEED = 253;
const int mu_CT_TAIL_USED = 254;
const int mu_CT_HEAD_USED = 255;
const int mu_CO_FETCH = 256;
const int mu_CO_LOAD = 257;
const int mu_CO_STORE = 258;
const int mu_TS_NORM_NULL = 259;
const int mu_TS_NORM_CODE = 260;
const int mu_TS_RESP_FAKE = 261;
const int mu_TS_RESP_CODE = 262;
const int mu_TS_CORE_JUNK = 263;
const int mu_TS_RESP_SIZE = 264;
const int mu_TS_RESP_DIFF = 265;
const int mu_TS_LINK_DEAD = 266;
const int mu_TS_LOST_TIDS = 267;
const int mu_TS_TIME_TIDS = 268;
const int mu_TS_SEND_TYPE = 269;
const int mu_TS_SEND_ADDR = 270;
const int mu_TS_TIME_BUSY = 271;
const int mu_TS_TIME_RESP = 272;
const int mu_TS_RESP_IDS = 273;
const int mu_TS_RESP_BAD = 274;
const int mu_TS_LOCK_BEFORE = 275;
const int mu_TS_LOCK_DURING = 276;
const int mu_TS_MTAG_STATE = 277;
const int mu_TS_CTAG_STATE = 278;
const int mu_TS_CODE_NULL = 279;
const int mu_FF_FIND = 280;
const int mu_FF_WAIT = 281;
const int mu_FF_LOAD = 282;
const int mu_FF_STORE = 283;
const int mu_FF_LOCK = 284;
const int mu_FF_ENQOLB = 285;
const int mu_FF_INDEX = 286;
const int mu_CU_BYPASS = 287;
const int mu_CU_LOCAL = 288;
const int mu_CU_GLOBAL = 289;
const int mu_SG_NONE = 290;
const int mu_SG_INVALID = 291;
const int mu_SG_STALE = 292;
const int mu_SG_GLOBAL = 293;
const int mu_SG_LOCAL = 294;
const int mu_I_NONE = 295;
const int mu_I_LOAD = 296;
const int mu_I_STORE = 297;
const int mu_I_FLUSH = 298;
const int mu_I_DELETE = 299;
const int mu_I_LOCK = 300;
const int mu_I_START = 301;
const int mu_I_ALLOCATE = 302;
const int mu_I_SETUP = 303;
const int mu_I_CLEANUP = 304;
/*** Variable declaration ***/
mu_1_BypassOptions mu_cacheUsage("cacheUsage",0);

/*** Variable declaration ***/
mu_1__type_2 mu_proc("proc",2);

/*** Variable declaration ***/
mu_1__type_3 mu_memory("memory",266);

void mu_UndefineUnusedValues()
{
{
for(int mu_i = 1; mu_i <= 2; mu_i++) {
{
for(int mu_j = 5; mu_j <= 5; mu_j++) {
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_j];
switch ((int) mu_line.mu_cState) {
case mu_CS_INVALID:
mu_line.undefine();
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CS_ONLY_DIRTY:
case mu_CS_ONLY_CLEAN:
case mu_CS_ONLY_FRESH:
mu_line.mu_forwId.undefine();
mu_line.mu_backId.undefine();
break;
case mu_CS_HEAD_DIRTY:
case mu_CS_HEAD_CLEAN:
case mu_CS_HEAD_FRESH:
mu_line.mu_backId.undefine();
break;
case mu_CS_TAIL_COPY:
case mu_CS_TAIL_VALID:
mu_line.mu_forwId.undefine();
break;
}
}
};
};
};
};
{
for(int mu_i = 3; mu_i <= 3; mu_i++) {
{
for(int mu_j = 4; mu_j <= 4; mu_j++) {
if ( (mu_memory[mu_i].mu_line[mu_j].mu_mState) == (mu_MS_HOME) )
{
mu_memory[mu_i].mu_line[mu_j].mu_forwId.undefine();
}
};
};
};
};
};
/*** end procedure declaration ***/

void mu_UndefineUnusedRes(mu_1_ResPacket& mu_p)
{
if ( mu_p.mu_cn )
{
mu_p.mu_co.undefine();
mu_p.mu_data.undefine();
mu_p.mu_forwId.undefine();
mu_p.mu_backId.undefine();
}
else
{
if ( (mu_p.mu_cmd) == (mu_SC_RESP00) )
{
mu_p.mu_data.undefine();
}
}
};
/*** end procedure declaration ***/

void mu_UndefineUnusedReq(mu_1_ReqPacket& mu_p)
{
if ( (mu_p.mu_cmd) != (mu_SC_MWRITE64) )
{
mu_p.mu_data.undefine();
}
};
/*** end procedure declaration ***/

void mu_SendResPacket(mu_1_ResPacket& mu_p, const mu_1_ProcId& mu_i)
{
{
  mu_1_ResPacket& mu_resP = mu_proc[mu_i].mu_exec.mu_resPacket;
mu_resP = mu_p;
mu_UndefineUnusedRes ( mu_resP );
}
};
/*** end procedure declaration ***/

void mu_SetReqPacket(const mu_1_ProcId& mu_i, mu_1_ReqPacket& mu_p, const mu_1_NodeId& mu_target, const mu_1_AccessCommandsReq& mu_cmd, const mu_1_MemoryCacheCommands& mu_mopCop, const mu_0_boolean& mu_s, const mu_0_boolean& mu_eh)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_p.undefine();
if (mu_target.isundefined())
  mu_p.mu_targetId.undefine();
else
  mu_p.mu_targetId = mu_target;
if (mu_cmd.isundefined())
  mu_p.mu_cmd.undefine();
else
  mu_p.mu_cmd = mu_cmd;
if (mu_i.isundefined())
  mu_p.mu_sourceId.undefine();
else
  mu_p.mu_sourceId = mu_i;
if ( !(mu_line.mu_addrOffset.isundefined()) )
{
mu_p.mu_offset = mu_line.mu_addrOffset;
}
if (mu_mopCop.isundefined())
  mu_p.mu_mopCop.undefine();
else
  mu_p.mu_mopCop = mu_mopCop;
if (mu_s.isundefined())
  mu_p.mu_s.undefine();
else
  mu_p.mu_s = mu_s;
if (mu_eh.isundefined())
  mu_p.mu_eh.undefine();
else
  mu_p.mu_eh = mu_eh;
if ( !(mu_line.mu_data.isundefined()) )
{
mu_p.mu_data = mu_line.mu_data;
}
}
};
/*** end procedure declaration ***/

void mu_SendReqPacket(const mu_1_ProcId& mu_i, mu_1_ReqPacket& mu_p)
{
{
  mu_1_ReqPacket& mu_reqP = mu_proc[mu_i].mu_exec.mu_reqPacket;
mu_reqP = mu_p;
mu_UndefineUnusedReq ( mu_reqP );
}
};
/*** end procedure declaration ***/

void mu_RemoveReqPacket(mu_1_ReqPacket& mu_p)
{
mu_p.undefine();
};
/*** end procedure declaration ***/

void mu_RemoveResPacket(mu_1_ResPacket& mu_p)
{
mu_p.undefine();
};
/*** end procedure declaration ***/

mu_1_DataFlags mu_MemoryTagLockUpdate(mu_1_MemoryLine& mu_line,const mu_1_MemoryCacheCommands& mu_code)
{
switch ((int) mu_code) {
case mu_MC_LOCK_SET:
Error.Error("Error: MemoryTagLockUpdate: MC_LOCK_SET not implemented");
break;
case mu_MC_LOCK_CLEAR:
Error.Error("Error: MemoryTagLockUpdate: MC_LOCK_CLEAR not implemented");
break;
}
return mu_MISS_MORE;
	Error.Error("The end of function MemoryTagLockUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_MemoryTagFreshUpdate(mu_1_MemoryLine& mu_line,const mu_1_MemoryCacheCommands& mu_code,const mu_1_NodeId& mu_sourceId,const mu_1_NodeId& mu_nextId)
{
/*** Variable declaration ***/
mu_0_boolean mu_eq("eq",0);

switch ((int) mu_line.mu_mState) {
case mu_MS_FRESH:
case mu_MS_GONE:
case mu_MS_HOME:
break;
default:
Error.Error("Error: MemoryTagFreshUpdate: memory state not allowed");
break;
}
{
  mu_1_MemoryCacheStates& mu_s = mu_line.mu_mState;
if ( !(mu_line.mu_forwId.isundefined()) )
{
mu_eq = (mu_sourceId) == (mu_line.mu_forwId);
}
switch ((int) mu_code) {
case mu_MC_ATTACH_TO_LIST:
if ( (mu_s) == (mu_MS_HOME) )
{
return mu_FULL_NONE;
}
else
{
bool mu__boolexpr4;
  if (!(!(mu_eq))) mu__boolexpr4 = FALSE ;
  else {
  mu__boolexpr4 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr4 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
}
else
{
bool mu__boolexpr5;
  if (!(!(mu_eq))) mu__boolexpr5 = FALSE ;
  else {
  mu__boolexpr5 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr5 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
else
{
return mu_FULL_NULL;
}
}
}
break;
case mu_MC_ATTACH_TO_GONE:
bool mu__boolexpr6;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr6 = TRUE ;
  else {
bool mu__boolexpr7;
  if (!(!(mu_eq))) mu__boolexpr7 = FALSE ;
  else {
  mu__boolexpr7 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  mu__boolexpr6 = (mu__boolexpr7) ; 
}
if ( mu__boolexpr6 )
{
}
else
{
bool mu__boolexpr8;
  if (!(!(mu_eq))) mu__boolexpr8 = FALSE ;
  else {
  mu__boolexpr8 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr8 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
else
{
return mu_FULL_NULL;
}
}
break;
case mu_MC_FRESH_TO_HOME:
if ( (mu_s) == (mu_MS_HOME) )
{
}
else
{
bool mu__boolexpr9;
  if (!(!(mu_eq))) mu__boolexpr9 = FALSE ;
  else {
  mu__boolexpr9 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr9 )
{
mu_line.mu_mState = mu_MS_HOME;
}
else
{
bool mu__boolexpr10;
  if (!(!(mu_eq))) mu__boolexpr10 = FALSE ;
  else {
  mu__boolexpr10 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr10 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
else
{
return mu_FULL_NULL;
}
}
}
break;
case mu_MC_LIST_TO_GONE:
bool mu__boolexpr11;
bool mu__boolexpr12;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr12 = TRUE ;
  else {
bool mu__boolexpr13;
  if (!(!(mu_eq))) mu__boolexpr13 = FALSE ;
  else {
  mu__boolexpr13 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  mu__boolexpr12 = (mu__boolexpr13) ; 
}
  if (mu__boolexpr12) mu__boolexpr11 = TRUE ;
  else {
bool mu__boolexpr14;
  if (!(!(mu_eq))) mu__boolexpr14 = FALSE ;
  else {
  mu__boolexpr14 = ((mu_s) == (mu_MS_GONE)) ; 
}
  mu__boolexpr11 = (mu__boolexpr14) ; 
}
if ( mu__boolexpr11 )
{
return mu_FULL_NULL;
}
else
{
bool mu__boolexpr15;
  if (!(mu_eq)) mu__boolexpr15 = FALSE ;
  else {
  mu__boolexpr15 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr15 )
{
mu_line.mu_mState = mu_MS_GONE;
}
else
{
return mu_FULL_NONE;
}
}
break;
case mu_MC_LIST_TO_HOME:
bool mu__boolexpr16;
bool mu__boolexpr17;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr17 = TRUE ;
  else {
bool mu__boolexpr18;
  if (!(!(mu_eq))) mu__boolexpr18 = FALSE ;
  else {
  mu__boolexpr18 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  mu__boolexpr17 = (mu__boolexpr18) ; 
}
  if (mu__boolexpr17) mu__boolexpr16 = TRUE ;
  else {
bool mu__boolexpr19;
  if (!(!(mu_eq))) mu__boolexpr19 = FALSE ;
  else {
  mu__boolexpr19 = ((mu_s) == (mu_MS_GONE)) ; 
}
  mu__boolexpr16 = (mu__boolexpr19) ; 
}
if ( mu__boolexpr16 )
{
return mu_FULL_NULL;
}
else
{
bool mu__boolexpr20;
  if (!(mu_eq)) mu__boolexpr20 = FALSE ;
  else {
  mu__boolexpr20 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr20 )
{
mu_line.mu_mState = mu_MS_HOME;
}
else
{
mu_line.mu_mState = mu_MS_HOME;
return mu_FULL_NONE;
}
}
break;
case mu_MC_CACHE_FRESH:
if ( (mu_s) == (mu_MS_HOME) )
{
mu_line.mu_mState = mu_MS_FRESH;
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_DATA;
}
else
{
bool mu__boolexpr21;
  if (!(!(mu_eq))) mu__boolexpr21 = FALSE ;
  else {
  mu__boolexpr21 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr21 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
}
else
{
bool mu__boolexpr22;
  if (!(!(mu_eq))) mu__boolexpr22 = FALSE ;
  else {
  mu__boolexpr22 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr22 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
else
{
return mu_FULL_NULL;
}
}
}
break;
case mu_MC_CACHE_DIRTY:
case mu_MC_CACHE_CLEAN:
bool mu__boolexpr23;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr23 = TRUE ;
  else {
bool mu__boolexpr24;
  if (!(!(mu_eq))) mu__boolexpr24 = FALSE ;
  else {
  mu__boolexpr24 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  mu__boolexpr23 = (mu__boolexpr24) ; 
}
if ( mu__boolexpr23 )
{
mu_line.mu_mState = mu_MS_GONE;
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
}
else
{
bool mu__boolexpr25;
  if (!(!(mu_eq))) mu__boolexpr25 = FALSE ;
  else {
  mu__boolexpr25 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr25 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
else
{
return mu_FULL_NULL;
}
}
break;
case mu_MC_PASS_HEAD:
bool mu__boolexpr26;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr26 = TRUE ;
  else {
bool mu__boolexpr27;
  if (!(!(mu_eq))) mu__boolexpr27 = FALSE ;
  else {
  mu__boolexpr27 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  mu__boolexpr26 = (mu__boolexpr27) ; 
}
if ( mu__boolexpr26 )
{
return mu_FULL_NULL;
}
else
{
bool mu__boolexpr28;
  if (!(!(mu_eq))) mu__boolexpr28 = FALSE ;
  else {
  mu__boolexpr28 = ((mu_s) == (mu_MS_GONE)) ; 
}
if ( mu__boolexpr28 )
{
return mu_FULL_NULL;
}
else
{
bool mu__boolexpr29;
  if (!(mu_eq)) mu__boolexpr29 = FALSE ;
  else {
  mu__boolexpr29 = ((mu_s) == (mu_MS_FRESH)) ; 
}
if ( mu__boolexpr29 )
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
}
else
{
if (mu_nextId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_nextId;
return mu_FULL_NONE;
}
}
}
break;
case mu_MC_LIST_TO_FRESH:
bool mu__boolexpr30;
bool mu__boolexpr31;
  if ((mu_s) == (mu_MS_HOME)) mu__boolexpr31 = TRUE ;
  else {
  mu__boolexpr31 = ((mu_s) == (mu_MS_FRESH)) ; 
}
  if (mu__boolexpr31) mu__boolexpr30 = TRUE ;
  else {
bool mu__boolexpr32;
  if (!(!(mu_eq))) mu__boolexpr32 = FALSE ;
  else {
  mu__boolexpr32 = ((mu_s) == (mu_MS_GONE)) ; 
}
  mu__boolexpr30 = (mu__boolexpr32) ; 
}
if ( mu__boolexpr30 )
{
return mu_FULL_NULL;
}
else
{
mu_line.mu_mState = mu_MS_FRESH;
}
break;
case mu_MC_WASH_TO_FRESH:
return mu_FULL_NULL;
break;
default:
return mu_NORM_NULL;
break;
}
}
return mu_FULL_DATA;
	Error.Error("The end of function MemoryTagFreshUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_MemoryTagUpdate(mu_1_MemoryLine& mu_line,mu_1_ReqPacket& mu_inP)
{
/*** Variable declaration ***/
mu_1_DataFlags mu_update("update",0);

/*** Variable declaration ***/
mu_1_NodeId mu_nextId("nextId",4);

mu_update = mu_MemoryTagLockUpdate( mu_line, mu_inP.mu_mopCop );
if ( (mu_update) != (mu_MISS_MORE) )
{
return mu_update;
}
mu_nextId = (mu_inP.mu_eh) ? (mu_inP.mu_newId) : (mu_inP.mu_sourceId);
if ( mu_MOP_FRESH )
{
return mu_MemoryTagFreshUpdate( mu_line, mu_inP.mu_mopCop, mu_inP.mu_sourceId, mu_nextId );
}
Error.Error("Error: MemoryTagUpdate: only MOP_FRESH implemented");
	Error.Error("The end of function MemoryTagUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_SStatValues mu_MemoryAccessBasic(mu_1_MemoryLine& mu_line,mu_1_ReqPacket& mu_inP,mu_1_ResPacket& mu_outP)
{
switch ((int) mu_inP.mu_cmd) {
case mu_SC_MREAD:
if ( !(mu_inP.mu_s) )
{
mu_outP.mu_cmd = mu_SC_RESP00;
}
else
{
mu_outP.mu_data = mu_line.mu_data;
mu_outP.mu_cmd = mu_SC_RESP64;
}
break;
case mu_SC_MWRITE64:
mu_line.mu_data = mu_inP.mu_data;
mu_outP.mu_cmd = mu_SC_RESP00;
break;
default:
Error.Error("Error: MemoryAccessBasic: requested memory command not implemented");
break;
}
return mu_RESP_NORMAL;
	Error.Error("The end of function MemoryAccessBasic reached without returning values.");
};
/*** end function declaration ***/

mu_1_AccessTypes mu_CSTATE_TYPES(const mu_1_MemoryCacheStates& mu_s)
{
switch ((int) mu_s) {
case mu_CS_QUEUED_DIRTY:
case mu_CS_ONLY_DIRTY:
case mu_CS_QUEUED_FRESH:
case mu_CS_OD_spin_IN:
case mu_CS_OD_RETN_IN:
case mu_CS_INVALID:
return mu_CT_ONLY_DIRTY;
break;
case mu_CS_QUEUED_MODS:
case mu_CS_QUEUED_CLEAN:
case mu_CS_HEAD_DIRTY:
return mu_CT_HEAD_DIRTY;
break;
case mu_CS_HD_INVAL_OD:
case mu_CS_ONLYQ_DIRTY:
case mu_CS_MID_COPY:
case mu_CS_MID_VALID:
case mu_CS_MV_back_IN:
case mu_CS_MV_forw_MV:
case mu_CS_QUEUED_JUNK:
case mu_CS_PENDING:
return mu_CT_MID_VALID;
break;
case mu_CS_TAIL_COPY:
case mu_CS_TAIL_VALID:
case mu_CS_MID_IDLE:
case mu_CS_HEAD_IDLE:
case mu_CS_MI_back_IN:
case mu_CS_MI_forw_MI:
return mu_CT_HEAD_IDLE;
break;
case mu_CS_OF_MODS_OD:
case mu_CS_ONLY_FRESH:
case mu_CS_HX_FORW_OX:
case mu_CS_HX_FORW_HX:
case mu_CS_QUEUED_HOME:
case mu_CS_OF_retn_IN:
return mu_CT_ONLY_FRESH;
break;
case mu_CS_HF_MODS_HD:
case mu_CS_HEAD_FRESH:
case mu_CS_HX_INVAL_OX:
return mu_CT_HEAD_FRESH;
break;
case mu_CS_ONLYP_DIRTY:
case mu_CS_HW_WASH_HF:
case mu_CS_LOCAL_CLEAN:
case mu_CS_QF_FLUSH_IN:
case mu_CS_TV_back_IN:
case mu_CS_TO_INVALID:
return mu_CT_ONLYP_DIRTY;
break;
case mu_CS_LOCAL_DIRTY:
case mu_CS_HEAD_VALID:
case mu_CS_HX_retn_IN:
case mu_CS_HEAD_STALE1:
case mu_CS_HEAD_STALE0:
return mu_CT_HEAD_RETN;
break;
case mu_CS_HX_XXXX_OD:
case mu_CS_ONLY_CLEAN:
case mu_CS_HEAD_CLEAN:
case mu_CS_OC_retn_IN:
case mu_CS_HX_PEND_HX:
case mu_CS_H1_PEND_HX:
case mu_CS_H0_PEND_HX:
return mu_CT_HEAD_CLEAN;
break;
case mu_CS_TX_XXXX_OD:
case mu_CS_HEAD_WASH:
case mu_CS_TV_mark_TS:
case mu_CS_TS_copy_TV:
case mu_CS_TS1_Move_TE:
case mu_CS_TS0_Move_TE:
return mu_CT_HEAD_WASH;
break;
case mu_CS_TD_mark_TE:
case mu_CS_TAIL_EXCL:
case mu_CS_TAIL_DIRTY:
case mu_CS_TE_back_IN:
case mu_CS_TS_back_IN:
case mu_CS_TD_back_IN:
case mu_CS_TV_mark_TE:
return mu_CT_TAIL_EXCL;
break;
case mu_CS_HD_MARK_HE:
case mu_CS_HEAD_EXCL:
case mu_CS_HV_MARK_HE:
case mu_CS_TAIL_STALE1:
case mu_CS_TAIL_STALE0:
case mu_CS_TI_back_IN:
case mu_CS_TAIL_IDLE:
return mu_CT_HEAD_EXCL;
break;
case mu_CS_TAIL_NEED:
case mu_CS_ONLY_USED:
case mu_CS_OD_CLEAN_OC:
case mu_CS_TN_send_TI:
case mu_CS_TN_send_TS:
case mu_CS_TN_back_IN:
return mu_CT_ONLY_USED;
break;
case mu_CS_HEAD_NEED:
case mu_CS_HD_CLEAN_HC:
case mu_CS_HV_MARK_HS:
case mu_CS_HS_COPY_HV:
case mu_CS_HS1_MOVE_HE:
case mu_CS_HS0_MOVE_HE:
return mu_CT_HEAD_NEED;
break;
case mu_CS_TAIL_USED:
case mu_CS_HD_WASH_HF:
case mu_CS_HN_SEND_HI:
case mu_CS_HN_SEND_HS:
case mu_CS_SS_next_IN:
case mu_CS_SAVE_STALE:
return mu_CT_TAIL_USED;
break;
case mu_CS_HEAD_USED:
case mu_CS_TS1_Move_TI:
case mu_CS_TS0_Move_TI:
case mu_CS_HS1_MOVE_HI:
case mu_CS_HS0_MOVE_HI:
return mu_CT_HEAD_USED;
break;
default:
Error.Error("Error: CSTATE_TYPES: cache state not allowed");
break;
}
	Error.Error("The end of function CSTATE_TYPES reached without returning values.");
};
/*** end function declaration ***/

mu_1_CacheLineId mu_CacheCheckSample(const mu_1_ProcId& mu_i,const mu_1_MemoryLineId& mu_offset,const mu_1_NodeId& mu_mem,const mu_1_CacheLineId& mu_k)
{
return mu_k;
	Error.Error("The end of function CacheCheckSample reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagLockUpdate(mu_1_CacheLine& mu_line,const mu_1_MemoryCacheCommands& mu_code)
{
switch ((int) mu_code) {
case mu_CC_LOCK_SET:
Error.Error("Error: CacheTagLockUpdate: CC_LOCK_SET not implemented");
break;
case mu_CC_LOCK_CLEAR:
Error.Error("Error: CacheTagLockUpdate: CC_LOCK_CLEAR not implemented");
break;
}
return mu_MISS_MORE;
	Error.Error("The end of function CacheTagLockUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagBasicUpdate(mu_1_CacheLine& mu_line,const mu_1_MemoryCacheCommands& mu_code,const mu_1_NodeId& mu_sourceId,const mu_1_NodeId& mu_newId)
{
/*** Variable declaration ***/
mu_1_DataFlags mu_goodData("goodData",0);

{
  mu_1_MemoryCacheStates& mu_s = mu_line.mu_cState;
mu_goodData = ((mu_code) == (mu_CC_PEND_VALID)) ? (mu_NORM_NONE) : (mu_NORM_DATA);
switch ((int) mu_s) {
case mu_CS_TV_back_IN:
case mu_CS_OF_retn_IN:
case mu_CS_OD_spin_IN:
case mu_CS_TAIL_VALID:
case mu_CS_ONLY_DIRTY:
case mu_CS_ONLY_FRESH:
break;
case mu_CS_TO_INVALID:
case mu_CS_OD_RETN_IN:
case mu_CS_HX_INVAL_OX:
case mu_CS_HD_INVAL_OD:
case mu_CS_QUEUED_DIRTY:
case mu_CS_QUEUED_JUNK:
case mu_CS_PENDING:
case mu_CS_INVALID:
return mu_MISS_MORE;
break;
default:
return mu_MISS_NONE;
break;
}
switch ((int) mu_code) {
case mu_CC_COPY_QOLB:
case mu_CC_COPY_STALE:
case mu_CC_COPY_VALID:
case mu_CC_PEND_VALID:
switch ((int) mu_s) {
case mu_CS_ONLY_DIRTY:
case mu_CS_ONLY_FRESH:
bool mu__boolexpr33;
  if (!((mu_s) == (mu_CS_ONLY_FRESH))) mu__boolexpr33 = FALSE ;
  else {
  mu__boolexpr33 = (mu_COP_CLEAN) ; 
}
if ( mu__boolexpr33 )
{
}
else
{
if (mu_sourceId.isundefined())
  mu_line.mu_backId.undefine();
else
  mu_line.mu_backId = mu_sourceId;
mu_s = mu_CS_TAIL_VALID;
return mu_goodData;
}
break;
case mu_CS_OD_spin_IN:
case mu_CS_OF_retn_IN:
if (mu_sourceId.isundefined())
  mu_line.mu_backId.undefine();
else
  mu_line.mu_backId = mu_sourceId;
mu_s = mu_CS_TV_back_IN;
return mu_goodData;
break;
}
break;
case mu_CC_FRESH_INVALID:
switch ((int) mu_s) {
case mu_CS_ONLY_FRESH:
mu_line.mu_cState = mu_CS_INVALID;
return mu_NORM_NONE;
break;
case mu_CS_OF_retn_IN:
mu_s = mu_CS_TO_INVALID;
return mu_NORM_NONE;
break;
}
break;
case mu_CC_VALID_INVALID:
switch ((int) mu_s) {
case mu_CS_TAIL_VALID:
mu_line.mu_cState = mu_CS_INVALID;
return mu_NORM_NONE;
break;
case mu_CS_TV_back_IN:
mu_s = mu_CS_TO_INVALID;
return mu_NORM_NONE;
break;
}
break;
case mu_CC_NEXT_FHEAD:
switch ((int) mu_s) {
case mu_CS_TAIL_VALID:
if ( (mu_line.mu_backId) != (mu_sourceId) )
{
}
else
{
mu_s = mu_CS_ONLY_FRESH;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_NEXT_DHEAD:
case mu_CC_NEXT_CHEAD:
bool mu__boolexpr34;
  if (!((mu_code) == (mu_CC_NEXT_CHEAD))) mu__boolexpr34 = FALSE ;
  else {
  mu__boolexpr34 = (mu_COP_CLEAN) ; 
}
if ( mu__boolexpr34 )
{
return mu_MISS_MORE;
}
switch ((int) mu_s) {
case mu_CS_TAIL_VALID:
if ( (mu_sourceId) != (mu_line.mu_backId) )
{
}
else
{
mu_s = mu_CS_ONLY_DIRTY;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_NEXT_VMID:
switch ((int) mu_s) {
case mu_CS_TAIL_VALID:
if ( (mu_sourceId) != (mu_line.mu_backId) )
{
}
else
{
if (mu_newId.isundefined())
  mu_line.mu_backId.undefine();
else
  mu_line.mu_backId = mu_newId;
return mu_NORM_NONE;
}
break;
}
break;
}
return mu_MISS_MORE;
}
	Error.Error("The end of function CacheTagBasicUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagDirtyUpdate(mu_1_CacheLine& mu_line,const mu_1_MemoryCacheCommands& mu_code,const mu_1_NodeId& mu_sourceId,const mu_1_NodeId& mu_newId)
{
/*** Variable declaration ***/
mu_1_DataFlags mu_goodData("goodData",0);

{
  mu_1_MemoryCacheStates& mu_s = mu_line.mu_cState;
mu_goodData = ((mu_code) == (mu_CC_PEND_VALID)) ? (mu_NORM_NONE) : (mu_NORM_DATA);
switch ((int) mu_s) {
case mu_CS_MV_back_IN:
case mu_CS_MV_forw_MV:
case mu_CS_MID_VALID:
case mu_CS_HX_retn_IN:
case mu_CS_HEAD_DIRTY:
case mu_CS_HEAD_FRESH:
case mu_CS_HX_FORW_HX:
break;
case mu_CS_HX_FORW_OX:
case mu_CS_QUEUED_MODS:
case mu_CS_QUEUED_CLEAN:
return mu_MISS_MORE;
break;
default:
return mu_MISS_NONE;
break;
}
switch ((int) mu_code) {
case mu_CC_COPY_QOLB:
case mu_CC_COPY_STALE:
case mu_CC_COPY_VALID:
case mu_CC_PEND_VALID:
switch ((int) mu_s) {
case mu_CS_HEAD_DIRTY:
case mu_CS_HEAD_FRESH:
bool mu__boolexpr35;
  if (!((mu_s) == (mu_CS_HEAD_FRESH))) mu__boolexpr35 = FALSE ;
  else {
  mu__boolexpr35 = (mu_COP_CLEAN) ; 
}
if ( mu__boolexpr35 )
{
}
else
{
if (mu_sourceId.isundefined())
  mu_line.mu_backId.undefine();
else
  mu_line.mu_backId = mu_sourceId;
mu_s = mu_CS_MID_VALID;
return mu_goodData;
}
break;
case mu_CS_HX_retn_IN:
mu_s = mu_CS_TO_INVALID;
return mu_NORM_NONE;
break;
}
break;
case mu_CC_FRESH_INVALID:
switch ((int) mu_s) {
case mu_CS_HEAD_FRESH:
mu_line.mu_cState = mu_CS_INVALID;
return mu_NORM_NONE;
break;
case mu_CS_HX_retn_IN:
mu_s = mu_CS_TO_INVALID;
return mu_NORM_NONE;
break;
}
break;
case mu_CC_VALID_INVALID:
switch ((int) mu_s) {
case mu_CS_MID_VALID:
mu_line.mu_cState = mu_CS_INVALID;
return mu_NORM_NONE;
break;
case mu_CS_MV_back_IN:
case mu_CS_MV_forw_MV:
mu_s = mu_CS_TO_INVALID;
return mu_NORM_NONE;
break;
}
break;
case mu_CC_NEXT_FHEAD:
switch ((int) mu_s) {
case mu_CS_MID_VALID:
if ( (mu_sourceId) != (mu_line.mu_backId) )
{
}
else
{
mu_s = mu_CS_HEAD_FRESH;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_NEXT_DHEAD:
case mu_CC_NEXT_CHEAD:
bool mu__boolexpr36;
  if (!((mu_code) == (mu_CC_NEXT_CHEAD))) mu__boolexpr36 = FALSE ;
  else {
  mu__boolexpr36 = (mu_COP_CLEAN) ; 
}
if ( mu__boolexpr36 )
{
return mu_MISS_MORE;
}
switch ((int) mu_s) {
case mu_CS_MID_VALID:
if ( (mu_sourceId) != (mu_line.mu_backId) )
{
}
else
{
mu_s = mu_CS_HEAD_DIRTY;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_NEXT_VMID:
switch ((int) mu_s) {
case mu_CS_MID_VALID:
if ( (mu_sourceId) != (mu_line.mu_backId) )
{
}
else
{
if (mu_newId.isundefined())
  mu_line.mu_backId.undefine();
else
  mu_line.mu_backId = mu_newId;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_PREV_VMID:
switch ((int) mu_s) {
case mu_CS_MV_forw_MV:
case mu_CS_MID_VALID:
case mu_CS_HX_FORW_HX:
case mu_CS_HEAD_DIRTY:
case mu_CS_HEAD_FRESH:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
if (mu_newId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_newId;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_PREV_VTAIL:
switch ((int) mu_s) {
case mu_CS_HEAD_FRESH:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
mu_s = mu_CS_ONLY_FRESH;
return mu_NORM_NONE;
}
break;
case mu_CS_HEAD_DIRTY:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
mu_s = mu_CS_ONLY_DIRTY;
return mu_NORM_NONE;
}
break;
case mu_CS_HX_FORW_HX:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
mu_s = mu_CS_HX_FORW_OX;
return mu_NORM_NONE;
}
break;
case mu_CS_MID_VALID:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
mu_s = mu_CS_TAIL_VALID;
return mu_NORM_NONE;
}
break;
case mu_CS_MV_forw_MV:
if ( (mu_sourceId) != (mu_line.mu_forwId) )
{
}
else
{
mu_s = mu_CS_TV_back_IN;
return mu_NORM_NONE;
}
break;
}
break;
}
return mu_MISS_MORE;
}
	Error.Error("The end of function CacheTagDirtyUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagFreshUpdate(mu_1_CacheLine& mu_line,const mu_1_MemoryCacheCommands& mu_code,const mu_1_NodeId& mu_sourceId,const mu_1_NodeId& mu_newId)
{
switch ((int) mu_line.mu_cState) {
case mu_CS_QUEUED_FRESH:
break;
default:
return mu_MISS_NONE;
break;
}
return mu_MISS_MORE;
	Error.Error("The end of function CacheTagFreshUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagModsUpdate(mu_1_CacheLine& mu_line,const mu_1_MemoryCacheCommands& mu_code,const mu_1_NodeId& mu_sourceId,const mu_1_NodeId& mu_newId)
{
{
  mu_1_MemoryCacheStates& mu_s = mu_line.mu_cState;
switch ((int) mu_s) {
case mu_CS_HF_MODS_HD:
break;
case mu_CS_OF_MODS_OD:
return mu_MISS_MORE;
break;
default:
return mu_MISS_NONE;
break;
}
switch ((int) mu_code) {
case mu_CC_PREV_VMID:
switch ((int) mu_s) {
case mu_CS_HF_MODS_HD:
if ( (mu_line.mu_forwId) != (mu_sourceId) )
{
}
else
{
if (mu_newId.isundefined())
  mu_line.mu_forwId.undefine();
else
  mu_line.mu_forwId = mu_newId;
return mu_NORM_NONE;
}
break;
}
break;
case mu_CC_PREV_VTAIL:
switch ((int) mu_s) {
case mu_CS_HF_MODS_HD:
if ( (mu_line.mu_forwId) != (mu_sourceId) )
{
}
else
{
mu_s = mu_CS_OF_MODS_OD;
return mu_NORM_NONE;
}
break;
}
break;
}
return mu_MISS_MORE;
}
	Error.Error("The end of function CacheTagModsUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_1_DataFlags mu_CacheTagUpdate(mu_1_CacheLine& mu_line,mu_1_ReqPacket& mu_inP)
{
/*** Variable declaration ***/
mu_1_DataFlags mu_status("status",0);

/*** Variable declaration ***/
mu_0_boolean mu_legal("legal",4);

mu_status = mu_CacheTagLockUpdate( mu_line, mu_inP.mu_mopCop );
if ( (mu_status) != (mu_MISS_MORE) )
{
return mu_status;
}
mu_status = mu_CacheTagBasicUpdate( mu_line, mu_inP.mu_mopCop, mu_inP.mu_sourceId, mu_inP.mu_newId );
bool mu__boolexpr37;
  if (!((mu_status) != (mu_MISS_MORE))) mu__boolexpr37 = FALSE ;
  else {
  mu__boolexpr37 = ((mu_status) != (mu_MISS_NONE)) ; 
}
if ( mu__boolexpr37 )
{
return mu_status;
}
mu_legal = (mu_status) != (mu_MISS_NONE);
if ( mu_COP_DIRTY )
{
mu_status = mu_CacheTagDirtyUpdate( mu_line, mu_inP.mu_mopCop, mu_inP.mu_sourceId, mu_inP.mu_newId );
bool mu__boolexpr38;
  if (!((mu_status) != (mu_MISS_MORE))) mu__boolexpr38 = FALSE ;
  else {
  mu__boolexpr38 = ((mu_status) != (mu_MISS_NONE)) ; 
}
if ( mu__boolexpr38 )
{
return mu_status;
}
bool mu__boolexpr39;
  if (mu_legal) mu__boolexpr39 = TRUE ;
  else {
  mu__boolexpr39 = ((mu_status) != (mu_MISS_NONE)) ; 
}
mu_legal = mu__boolexpr39;
}
if ( mu_COP_FRESH )
{
mu_status = mu_CacheTagFreshUpdate( mu_line, mu_inP.mu_mopCop, mu_inP.mu_sourceId, mu_inP.mu_newId );
bool mu__boolexpr40;
  if (!((mu_status) != (mu_MISS_MORE))) mu__boolexpr40 = FALSE ;
  else {
  mu__boolexpr40 = ((mu_status) != (mu_MISS_NONE)) ; 
}
if ( mu__boolexpr40 )
{
return mu_status;
}
bool mu__boolexpr41;
  if (mu_legal) mu__boolexpr41 = TRUE ;
  else {
  mu__boolexpr41 = ((mu_status) != (mu_MISS_NONE)) ; 
}
mu_legal = mu__boolexpr41;
}
if ( mu_COP_MODS )
{
mu_status = mu_CacheTagModsUpdate( mu_line, mu_inP.mu_mopCop, mu_inP.mu_sourceId, mu_inP.mu_newId );
bool mu__boolexpr42;
  if (!((mu_status) != (mu_MISS_MORE))) mu__boolexpr42 = FALSE ;
  else {
  mu__boolexpr42 = ((mu_status) != (mu_MISS_NONE)) ; 
}
if ( mu__boolexpr42 )
{
return mu_status;
}
bool mu__boolexpr43;
  if (mu_legal) mu__boolexpr43 = TRUE ;
  else {
  mu__boolexpr43 = ((mu_status) != (mu_MISS_NONE)) ; 
}
mu_legal = mu__boolexpr43;
}
if ( !(mu_legal) ) Error.Error("Assertion failed: CacheTagUpdate: legal not true");
return mu_NORM_NULL;
	Error.Error("The end of function CacheTagUpdate reached without returning values.");
};
/*** end function declaration ***/

mu_0_boolean mu_CodeFault(const mu_1_ProcId& mu_i)
{
switch ((int) mu_proc[mu_i].mu_exec.mu_state.mu_tStat) {
case mu_TS_NORM_CODE:
case mu_TS_NORM_NULL:
break;
default:
return mu_true;
break;
}
return mu_false;
	Error.Error("The end of function CodeFault reached without returning values.");
};
/*** end function declaration ***/

void mu_CodeSetTStat(const mu_1_ProcId& mu_i, const mu_1_TransactStatus& mu_code)
{
if (mu_code.isundefined())
  mu_proc[mu_i].mu_exec.mu_state.mu_tStat.undefine();
else
  mu_proc[mu_i].mu_exec.mu_state.mu_tStat = mu_code;
};
/*** end procedure declaration ***/

mu_1_StableGroups mu_TypicalStableStates(const mu_1_MemoryCacheStates& mu_s)
{
switch ((int) mu_s) {
case mu_CS_INVALID:
return mu_SG_INVALID;
break;
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
case mu_CS_HEAD_FRESH:
case mu_CS_HEAD_DIRTY:
case mu_CS_ONLY_FRESH:
case mu_CS_ONLY_DIRTY:
return mu_SG_GLOBAL;
break;
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
return mu_SG_LOCAL;
break;
default:
return mu_SG_NONE;
break;
}
	Error.Error("The end of function TypicalStableStates reached without returning values.");
};
/*** end function declaration ***/

void mu_CacheReadSrc(const mu_1_ProcId& mu_i, const mu_1_AccessCommandsReq& mu_cmd, const mu_1_MemoryCacheCommands& mu_mopCop, const mu_0_boolean& mu_s, const mu_1_ProcId& mu_target)
{
/*** Variable declaration ***/
mu_1_ReqPacket mu_outP("outP",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_SetReqPacket ( mu_i, mu_outP, (int)mu_target, mu_cmd, mu_mopCop, mu_s, mu_true );
if ( !(mu_line.mu_memId.isundefined()) )
{
mu_outP.mu_memId = mu_line.mu_memId;
}
mu_SendReqPacket ( mu_i, mu_outP );
}
};
/*** end procedure declaration ***/

void mu_CacheReadNew(const mu_1_ProcId& mu_i, const mu_1_AccessCommandsReq& mu_cmd, const mu_1_MemoryCacheCommands& mu_mopCop, const mu_0_boolean& mu_s, const mu_1_ProcId& mu_target, const mu_1_NodeId& mu_newId)
{
/*** Variable declaration ***/
mu_1_ReqPacket mu_outP("outP",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_SetReqPacket ( mu_i, mu_outP, (int)mu_target, mu_cmd, mu_mopCop, mu_s, mu_true );
if (mu_newId.isundefined())
  mu_outP.mu_newId.undefine();
else
  mu_outP.mu_newId = mu_newId;
if ( !(mu_line.mu_memId.isundefined()) )
{
mu_outP.mu_memId = mu_line.mu_memId;
}
mu_SendReqPacket ( mu_i, mu_outP );
}
};
/*** end procedure declaration ***/

void mu_MemoryUpdateSrc(const mu_1_ProcId& mu_i, const mu_1_AccessCommandsReq& mu_cmd, const mu_1_MemoryCacheCommands& mu_mopCop, const mu_0_boolean& mu_s)
{
/*** Variable declaration ***/
mu_1_ReqPacket mu_outP("outP",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_SetReqPacket ( mu_i, mu_outP, mu_line.mu_memId, mu_cmd, mu_mopCop, mu_s, mu_false );
if ( !(!(mu_line.mu_memId.isundefined())) ) Error.Error("Assertion failed: MemoryUpdateSrc: target undefined");
mu_SendReqPacket ( mu_i, mu_outP );
}
};
/*** end procedure declaration ***/

void mu_MemoryUpdateNew(const mu_1_ProcId& mu_i, const mu_1_AccessCommandsReq& mu_cmd, const mu_1_MemoryCacheCommands& mu_mopCop, const mu_0_boolean& mu_s, const mu_1_NodeId& mu_newId)
{
/*** Variable declaration ***/
mu_1_ReqPacket mu_outP("outP",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_SetReqPacket ( mu_i, mu_outP, mu_line.mu_memId, mu_cmd, mu_mopCop, mu_s, mu_true );
if (mu_newId.isundefined())
  mu_outP.mu_newId.undefine();
else
  mu_outP.mu_newId = mu_newId;
if ( !(!(mu_line.mu_memId.isundefined())) ) Error.Error("Assertion failed: MemoryUpdateNew: target undefined");
mu_SendReqPacket ( mu_i, mu_outP );
}
};
/*** end procedure declaration ***/

void mu_TailValidDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CS_TV_back_IN)) ) Error.Error("Assertion failed: TailValidDoInvalid: cache line state not CS_TV_back_IN");
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_PREV_VTAIL, mu_false, (int)mu_line.mu_backId );
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_TO_INVALID:
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CS_TV_back_IN:
if ( mu_inP.mu_cn )
{
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_PREV_VTAIL, mu_false, (int)mu_line.mu_backId );
mu_exit = mu_true;
return ;
}
mu_line.mu_cState = mu_CS_INVALID;
break;
default:
Error.Error("Error: TailValidDoInvalid: cache line state not allowed");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: TailValidDoInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_AttachLists(const mu_1_ProcId& mu_i, const mu_1_MemoryCacheCommands& mu_command, const mu_0_boolean& mu_size, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit, mu_1_AttachStatus& mu_aStatus)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_MemoryCacheStates& mu_oldState = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2.mu_cState;
mu_aStatus.undefine();
if ( mu_firstEntry )
{
bool mu__boolexpr44;
bool mu__boolexpr45;
bool mu__boolexpr46;
bool mu__boolexpr47;
  if (!((mu_command) == (mu_CC_PEND_VALID))) mu__boolexpr47 = FALSE ;
  else {
  mu__boolexpr47 = (!(mu_size)) ; 
}
  if (mu__boolexpr47) mu__boolexpr46 = TRUE ;
  else {
bool mu__boolexpr48;
  if (!((mu_command) == (mu_CC_COPY_VALID))) mu__boolexpr48 = FALSE ;
  else {
  mu__boolexpr48 = (mu_size) ; 
}
  mu__boolexpr46 = (mu__boolexpr48) ; 
}
  if (mu__boolexpr46) mu__boolexpr45 = TRUE ;
  else {
bool mu__boolexpr49;
  if (!((mu_command) == (mu_CC_COPY_STALE))) mu__boolexpr49 = FALSE ;
  else {
  mu__boolexpr49 = (mu_size) ; 
}
  mu__boolexpr45 = (mu__boolexpr49) ; 
}
  if (mu__boolexpr45) mu__boolexpr44 = TRUE ;
  else {
bool mu__boolexpr50;
  if (!((mu_command) == (mu_CC_COPY_QOLB))) mu__boolexpr50 = FALSE ;
  else {
  mu__boolexpr50 = (mu_size) ; 
}
  mu__boolexpr44 = (mu__boolexpr50) ; 
}
if ( mu__boolexpr44 )
{
}
else
{
Error.Error("Error: AttachLists: illegal cache command");
}
switch ((int) mu_line.mu_cState) {
case mu_CS_QUEUED_FRESH:
case mu_CS_QUEUED_CLEAN:
case mu_CS_QUEUED_JUNK:
break;
default:
Error.Error("Error: AttachLists: illegal cache line state");
break;
}
mu_oldState = mu_line.mu_cState;
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_command, mu_size, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( (mu_line.mu_cState) != (mu_oldState) )
{
Error.Error("Error: AttachLists: POP_WEAK not implemented");
}
if ( mu_inP.mu_cn )
{
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_command, mu_size, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
mu_aStatus.mu_cState = mu_inP.mu_mCState;
if ( !(mu_inP.mu_backId.isundefined()) )
{
mu_aStatus.mu_backId = mu_inP.mu_backId;
}
switch ((int) mu_CSTATE_TYPES( mu_inP.mu_mCState )) {
case mu_CT_ONLY_USED:
case mu_CT_HEAD_WASH:
case mu_CT_HEAD_DIRTY:
case mu_CT_HEAD_FRESH:
case mu_CT_ONLY_FRESH:
case mu_CT_HEAD_CLEAN:
case mu_CT_MID_VALID:
case mu_CT_ONLYP_DIRTY:
case mu_CT_ONLY_DIRTY:
break;
case mu_CT_HEAD_NEED:
case mu_CT_TAIL_USED:
case mu_CT_TAIL_EXCL:
case mu_CT_HEAD_USED:
case mu_CT_HEAD_EXCL:
Error.Error("Error: AttachLists: cache line state not implemented");
break;
case mu_CT_HEAD_RETN:
case mu_CT_HEAD_IDLE:
bool mu__boolexpr51;
bool mu__boolexpr52;
  if (!((mu_CSTATE_TYPES( mu_inP.mu_mCState )) == (mu_CT_HEAD_IDLE))) mu__boolexpr52 = FALSE ;
  else {
  mu__boolexpr52 = ((mu_command) == (mu_CC_COPY_QOLB)) ; 
}
  if (!(mu__boolexpr52)) mu__boolexpr51 = FALSE ;
  else {
  mu__boolexpr51 = (mu_size) ; 
}
if ( mu__boolexpr51 )
{
mu_oldState.undefine();
return ;
}
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_command, mu_size, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
break;
default:
Error.Error("Error: AttachLists: cache line state not allowed");
break;
}
mu_oldState.undefine();
}
};
/*** end procedure declaration ***/

void mu_OnlyFreshDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L2& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2;
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CS_OF_retn_IN)) ) Error.Error("Assertion failed: OnlyFreshDoInvalid: cache line state not CS_OF_retn_IN");
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_HOME, mu_false );
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_TO_INVALID:
if ( !(mu_inP.mu_cn) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CS_TV_back_IN:
if ( mu_s.mu_firstEntrySub )
{
if ( !(mu_inP.mu_cn) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
}
mu_TailValidDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
break;
case mu_CS_OF_retn_IN:
if ( mu_inP.mu_cn )
{
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_HOME, mu_false );
mu_exit = mu_true;
return ;
}
if ( (mu_inP.mu_mCState) != (mu_MS_FRESH) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_cState = mu_CS_INVALID;
break;
default:
Error.Error("Error: OnlyFreshDoInvalid: cache line state not allowed");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyFreshDoInvalid: cache line state not CS_INVALID");
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_OnlyDirtyDoReturn(const mu_1_ProcId& mu_i, const mu_0_boolean& mu_save, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L2& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2;
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CS_OD_RETN_IN)) ) Error.Error("Assertion failed: OnlyDirtyDoReturn: cache line state not CS_OD_RETN_IN");
mu_MemoryUpdateSrc ( mu_i, (mu_save) ? (mu_SC_MWRITE64) : (mu_SC_MREAD), mu_MC_LIST_TO_HOME, mu_false );
mu_s.mu_firstLoop = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstLoop )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_OD_RETN_IN)) ) Error.Error("Assertion failed: OnlyDirtyDoReturn: cache line state not CS_OD_RETN_IN");
switch ((int) mu_inP.mu_mCState) {
case mu_MS_FRESH:
case mu_MS_HOME:
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
break;
}
if ( !(mu_inP.mu_cn) )
{
mu_line.mu_cState = mu_CS_INVALID;
mu_s.undefine();
return ;
}
mu_line.mu_cState = mu_CS_OD_spin_IN;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_GONE, mu_false );
mu_s.mu_firstLoop = mu_false;
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_TO_INVALID:
mu_line.mu_cState = mu_CS_INVALID;
mu_s.undefine();
return ;
break;
case mu_CS_TV_back_IN:
mu_TailValidDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyDirtyDoReturn: cache line state not CS_INVALID");
}
mu_s.undefine();
return ;
break;
case mu_CS_OD_spin_IN:
switch ((int) mu_inP.mu_mCState) {
case mu_MS_FRESH:
case mu_MS_HOME:
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
break;
}
if ( mu_inP.mu_cn )
{
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_GONE, mu_false );
mu_exit = mu_true;
return ;
}
break;
default:
Error.Error("Error: OnlyDirtyDoReturn: cache line state not allowed");
break;
}
mu_line.mu_cState = mu_CS_OD_RETN_IN;
mu_MemoryUpdateSrc ( mu_i, (mu_save) ? (mu_SC_MWRITE64) : (mu_SC_MREAD), mu_MC_LIST_TO_HOME, mu_false );
mu_s.mu_firstLoop = mu_true;
mu_exit = mu_true;
return ;
}
};
/*** end procedure declaration ***/

void mu_HalfGoneDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HalfGoneDoInvalid: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_HX_retn_IN)) ) Error.Error("Assertion failed: HalfGoneDoInvalid: cache line state not CS_HX_retn_IN");
mu_MemoryUpdateNew ( mu_i, mu_SC_MREAD, mu_MC_PASS_HEAD, mu_false, mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_TO_INVALID:
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CS_HX_retn_IN:
if ( mu_inP.mu_cn )
{
mu_MemoryUpdateNew ( mu_i, mu_SC_MREAD, mu_MC_PASS_HEAD, mu_false, mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
switch ((int) mu_inP.mu_mCState) {
case mu_MS_FRESH:
case mu_MS_HOME:
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
break;
}
mu_line.mu_cState = mu_CS_INVALID;
break;
default:
Error.Error("Error: HalfGoneDoInvalid: cache line state not allowed");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HalfGoneDoInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_ListValidDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L2& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_QF_FLUSH_IN:
case mu_CS_QUEUED_DIRTY:
case mu_CS_QUEUED_HOME:
case mu_CS_HX_INVAL_OX:
case mu_CS_HD_INVAL_OD:
break;
default:
Error.Error("Error: ListValidDoInvalid: cache line state not allowed");
break;
}
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_VALID_INVALID, mu_false, mu_s.mu_nextId );
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( mu_inP.mu_cn )
{
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_VALID_INVALID, mu_false, mu_s.mu_nextId );
mu_exit = mu_true;
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_inP.mu_mCState )) {
case mu_CT_MID_VALID:
mu_s.mu_nextId = mu_inP.mu_forwId;
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_VALID_INVALID, mu_false, mu_s.mu_nextId );
mu_exit = mu_true;
return ;
break;
default:
mu_s.undefine();
return ;
break;
}
}
};
/*** end procedure declaration ***/

void mu_HeadFreshDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L1& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l1;
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HeadFreshDoInvalid: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_HX_FORW_HX)) ) Error.Error("Assertion failed: HeadFreshDoInvalid: cache line state not CS_HX_FORW_HX");
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_NEXT_FHEAD, mu_false, (int)mu_line.mu_forwId );
mu_s.mu_firstLoop = mu_true;
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstLoop )
{
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_HX_FORW_OX:
if ( mu_s.mu_firstEntrySub )
{
mu_line.mu_cState = mu_CS_OF_retn_IN;
}
mu_OnlyFreshDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadFreshDoInvalid: cache line state not CS_INVALID");
mu_s.undefine();
return ;
break;
case mu_CS_HX_FORW_HX:
if ( mu_inP.mu_cn )
{
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_NEXT_FHEAD, mu_false, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
mu_line.mu_cState = mu_CS_HX_retn_IN;
break;
default:
Error.Error("Error: HeadFreshDoInvalid: cache line state not allowed");
break;
}
mu_MemoryUpdateNew ( mu_i, mu_SC_MREAD, mu_MC_PASS_HEAD, mu_false, mu_line.mu_forwId );
mu_s.mu_firstLoop = mu_false;
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_TO_INVALID:
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CS_HX_retn_IN:
if ( mu_inP.mu_cn )
{
mu_MemoryUpdateNew ( mu_i, mu_SC_MREAD, mu_MC_PASS_HEAD, mu_false, mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
if ( (mu_inP.mu_mCState) != (mu_MS_FRESH) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_cState = mu_CS_INVALID;
break;
default:
Error.Error("Error: HeadFreshDoInvalid: cache line state not allowed");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadFreshDoInvalid: cache line state not CS_INVALID");
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_MidValidToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L1& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l1;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_MID_VALID:
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: MidValidToInvalid: POP_DIRTY false");
break;
case mu_CS_MID_COPY:
if ( !(mu_POP_CLEAN) ) Error.Error("Assertion failed: MidValidToInvalid: POP_CLEAN false");
break;
default:
Error.Error("Error: MidValidToInvalid: cache line state not allowed");
break;
}
mu_line.mu_cState = mu_CS_MV_forw_MV;
mu_CacheReadNew ( mu_i, mu_SC_CREAD, mu_CC_NEXT_VMID, mu_false, (int)mu_line.mu_forwId, mu_line.mu_backId );
mu_s.mu_firstLoop = mu_true;
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstLoop )
{
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_TO_INVALID:
mu_line.mu_cState = mu_CS_INVALID;
mu_s.undefine();
return ;
break;
case mu_CS_TV_back_IN:
mu_TailValidDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: MidValidToInvalid: cache line state not CS_INVALID");
mu_s.undefine();
return ;
break;
case mu_CS_MV_forw_MV:
if ( mu_inP.mu_cn )
{
mu_CacheReadNew ( mu_i, mu_SC_CREAD, mu_CC_NEXT_VMID, mu_false, (int)mu_line.mu_forwId, mu_line.mu_backId );
mu_exit = mu_true;
return ;
}
break;
default:
Error.Error("Error: MidValidToInvalid: cache line state not allowed");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_MV_forw_MV)) ) Error.Error("Assertion failed: MidValidToInvalid: cache line state not CS_MV_forw_MV");
mu_line.mu_cState = mu_CS_MV_back_IN;
mu_CacheReadNew ( mu_i, mu_SC_CREAD, mu_CC_PREV_VMID, mu_false, (int)mu_line.mu_backId, mu_line.mu_forwId );
mu_s.mu_firstLoop = mu_false;
mu_exit = mu_true;
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_TO_INVALID:
break;
case mu_CS_MV_back_IN:
if ( mu_inP.mu_cn )
{
mu_CacheReadNew ( mu_i, mu_SC_CREAD, mu_CC_PREV_VMID, mu_false, (int)mu_line.mu_backId, mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
break;
default:
Error.Error("Error: MidValidToInvalid: cache line state not allowed");
break;
}
mu_line.mu_cState = mu_CS_INVALID;
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_InvalidDoHeadDirty(const mu_1_ProcId& mu_i, const mu_1_MemoryCacheCommands& mu_command, const mu_0_boolean& mu_size, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
/*** Variable declaration ***/
mu_1_AttachStatus mu_aStatus("aStatus",0);

/*** Variable declaration ***/
mu_1_MemoryCacheStates mu_temp("temp",10);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
if ( mu_firstEntry )
{
bool mu__boolexpr53;
  if (!(mu_s.mu_secondEntry.isundefined())) mu__boolexpr53 = FALSE ;
  else {
  mu__boolexpr53 = (mu_s.mu_mState.isundefined()) ; 
}
if ( !(mu__boolexpr53) ) Error.Error("Assertion failed: InvalidDoHeadDirty: routine uses level0 state !");
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: InvalidDoHeadDirty: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: InvalidDoHeadDirty: cache line state not CS_INVALID");
mu_line.mu_cState = mu_CS_PENDING;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_command, mu_size );
mu_s.mu_secondEntry = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_secondEntry )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_mState = mu_inP.mu_mCState;
if ( !((mu_line.mu_cState) == (mu_CS_PENDING)) ) Error.Error("Assertion failed: InvalidDoHeadDirty: cache line state not CS_PENDING");
if ( mu_inP.mu_cn )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
}
switch ((int) mu_s.mu_mState) {
case mu_MS_HOME:
mu_temp = mu_s.mu_mState;
mu_s.undefine();
if (mu_temp.isundefined())
  mu_s.mu_mState.undefine();
else
  mu_s.mu_mState = mu_temp;
return ;
break;
case mu_MS_FRESH:
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_temp = mu_s.mu_mState;
mu_s.undefine();
if (mu_temp.isundefined())
  mu_s.mu_mState.undefine();
else
  mu_s.mu_mState = mu_temp;
return ;
break;
case mu_MS_GONE:
if ( mu_s.mu_secondEntry )
{
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_line.mu_cState = mu_CS_QUEUED_JUNK;
}
mu_AttachLists ( mu_i, mu_CC_COPY_VALID, mu_true, mu_inP, mu_s.mu_secondEntry, mu_exit, mu_aStatus );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_aStatus.mu_cState )) {
case mu_CT_TAIL_EXCL:
case mu_CT_HEAD_EXCL:
case mu_CT_HEAD_DIRTY:
case mu_CT_MID_VALID:
case mu_CT_ONLYP_DIRTY:
case mu_CT_ONLY_DIRTY:
mu_line.mu_cState = mu_CI_HEAD_DIRTY;
break;
case mu_CT_HEAD_CLEAN:
case mu_CT_HEAD_WASH:
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CI_HEAD_CLEAN) : (mu_CI_HEAD_DIRTY);
break;
case mu_CT_TAIL_USED:
case mu_CT_HEAD_USED:
case mu_CT_HEAD_NEED:
case mu_CT_ONLY_USED:
mu_line.mu_cState = (mu_POP_QOLB) ? (mu_CI_HEADQ_DIRTY) : (mu_CI_HEAD_DIRTY);
break;
default:
Error.Error("Error: InvalidDoHeadDirty: attach status not allowed");
break;
}
break;
default:
Error.Error("Error: InvalidDoHeadDirty: memory line state not allowed or not implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_HEADQ_DIRTY:
case mu_CI_HEAD_DIRTY:
case mu_CI_HEAD_CLEAN:
break;
default:
Error.Error("Error: InvalidDoHeadDirty: cache line state not allowed");
break;
}
mu_temp = mu_s.mu_mState;
mu_s.undefine();
if (mu_temp.isundefined())
  mu_s.mu_mState.undefine();
else
  mu_s.mu_mState = mu_temp;
}
};
/*** end procedure declaration ***/

void mu_OnlyDirtyDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_ONLY_DIRTY:
if ( !(!(mu_POP_PAIR)) ) Error.Error("Assertion failed: OnlyDirtyDoInvalid: POP_PAIR true");
break;
case mu_CS_HX_FORW_OX:
case mu_CS_QUEUED_DIRTY:
case mu_CS_HD_INVAL_OD:
case mu_CS_HX_INVAL_OX:
case mu_CI_OD_FLUSH_IN:
break;
case mu_CS_ONLYP_DIRTY:
if ( !(mu_POP_PAIR) ) Error.Error("Assertion failed: OnlyDirtyDoInvalid: POP_PAIR false");
break;
case mu_CS_ONLY_USED:
case mu_CS_ONLYQ_DIRTY:
if ( !(mu_POP_QOLB) ) Error.Error("Assertion failed: OnlyDirtyDoInvalid: POP_QOLB false");
break;
case mu_CS_OD_CLEAN_OC:
if ( !(mu_POP_CLEANSE) ) Error.Error("Assertion failed: OnlyDirtyDoInvalid: POP_CLEANSE false");
break;
default:
Error.Error("Error: OnlyDirtyDoInvalid: cache line state not allowed");
break;
}
if ( mu_POP_ROBUST )
{
Error.Error("Error: OnlyDirtyDoInvalid: POP_ROBUST not implemented");
}
mu_line.mu_cState = mu_CS_OD_RETN_IN;
}
mu_OnlyDirtyDoReturn ( mu_i, mu_true, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyDirtyDoInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_HeadGoneDoInvalid(const mu_1_ProcId& mu_i, const mu_1_AccessCommandsReq& mu_aCmd, const mu_1_MemoryCacheCommands& mu_cmd, const mu_0_boolean& mu_size, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L1& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l1;
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HeadGoneDoInvalid: POP_DIRTY false");
switch ((int) mu_aCmd) {
case mu_SC_CREAD:
bool mu__boolexpr54;
  if (!((mu_cmd) == (mu_CC_NEXT_DHEAD))) mu__boolexpr54 = FALSE ;
  else {
  mu__boolexpr54 = (!(mu_size)) ; 
}
if ( mu__boolexpr54 )
{
}
else
{
bool mu__boolexpr55;
bool mu__boolexpr56;
  if (!((mu_cmd) == (mu_CC_NEXT_VHEAD))) mu__boolexpr56 = FALSE ;
  else {
  mu__boolexpr56 = (!(mu_size)) ; 
}
  if (mu__boolexpr56) mu__boolexpr55 = TRUE ;
  else {
bool mu__boolexpr57;
  if (!((mu_cmd) == (mu_CC_NEXT_SHEAD))) mu__boolexpr57 = FALSE ;
  else {
  mu__boolexpr57 = (!(mu_size)) ; 
}
  mu__boolexpr55 = (mu__boolexpr57) ; 
}
if ( mu__boolexpr55 )
{
if ( !(mu_POP_PAIR) ) Error.Error("Assertion failed: HeadGoneDoInvalid: POP_PAIR false");
}
else
{
bool mu__boolexpr58;
  if (!((mu_cmd) == (mu_CC_NEXT_IHEAD))) mu__boolexpr58 = FALSE ;
  else {
  mu__boolexpr58 = (!(mu_size)) ; 
}
if ( mu__boolexpr58 )
{
if ( !(mu_POP_QOLB) ) Error.Error("Assertion failed: HeadGoneDoInvalid: POP_QOLB false");
}
else
{
Error.Error("Error: HeadGoneDoInvalid: cache command not allowed or not implemented");
}
}
}
break;
default:
Error.Error("Error: HeadGoneDoInvalid: transaction command not allowed or not implemented");
break;
}
if ( !((mu_line.mu_cState) == (mu_CS_HX_FORW_HX)) ) Error.Error("Assertion failed: HeadGoneDoInvalid: cache line state not CS_HX_FORW_HX");
if ( (mu_aCmd) == (mu_SC_CREAD) )
{
mu_CacheReadSrc ( mu_i, mu_aCmd, mu_cmd, mu_size, (int)mu_line.mu_forwId );
}
else
{
Error.Error("Error: HeadGoneDoInvalid: transaction command not implemented");
}
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_HX_FORW_OX:
mu_OnlyDirtyDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
break;
case mu_CS_HX_FORW_HX:
if ( mu_s.mu_firstEntrySub )
{
if ( mu_inP.mu_cn )
{
if ( (mu_aCmd) == (mu_SC_CREAD) )
{
mu_CacheReadSrc ( mu_i, mu_aCmd, mu_cmd, mu_size, (int)mu_line.mu_forwId );
}
else
{
Error.Error("Error: HeadGoneDoInvalid: transaction command not implemented");
}
mu_exit = mu_true;
return ;
}
mu_line.mu_cState = mu_CS_HX_retn_IN;
}
mu_HalfGoneDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
break;
default:
Error.Error("Error: HeadGoneDoInvalid: cache line state not allowed");
break;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadGoneDoInvalid: cache line state not CS_INVALID");
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_ListFreshDoInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L1& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l1;
  mu_1_ProcId& mu_nextId = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_QUEUED_DIRTY:
break;
case mu_CS_QUEUED_HOME:
Error.Error("Error: ListFreshDoInvalid: POP_WRITE not implemented");
break;
case mu_CS_QF_FLUSH_IN:
Error.Error("Error: ListFreshDoInvalid: POP_FLUSH not implemented");
break;
default:
Error.Error("Error: ListFreshDoInvalid: cache line state not allowed");
break;
}
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_FRESH_INVALID, mu_false, (int)mu_line.mu_forwId );
mu_s.mu_firstEntrySub = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_firstEntrySub )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( mu_inP.mu_cn )
{
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_FRESH_INVALID, mu_false, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
}
mu_s.mu_cState = mu_inP.mu_mCState;
}
switch ((int) mu_CSTATE_TYPES( mu_s.mu_cState )) {
case mu_CT_ONLY_FRESH:
break;
case mu_CT_HEAD_FRESH:
if ( mu_s.mu_firstEntrySub )
{
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_nextId = mu_line.mu_forwId;
}
mu_ListValidDoInvalid ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
break;
case mu_CT_HEAD_RETN:
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_CacheReadSrc ( mu_i, mu_SC_CREAD, mu_CC_FRESH_INVALID, mu_false, (int)mu_line.mu_forwId );
mu_exit = mu_true;
return ;
break;
default:
Error.Error("Error: ListFreshDoInvalid: cache line state not allowed");
break;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_InvalidToHeadFresh(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
/*** Variable declaration ***/
mu_1_AttachStatus mu_aStatus("aStatus",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
if ( mu_firstEntry )
{
if ( !(mu_POP_FRESH) ) Error.Error("Assertion failed: InvalidToHeadFresh: POP_FRESH false");
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: InvalidToHeadFresh: cache line state not CS_INVALID");
mu_line.mu_cState = mu_CS_PENDING;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_CACHE_FRESH, mu_true );
mu_s.mu_secondEntry = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_secondEntry )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_PENDING)) ) Error.Error("Assertion failed: InvalidToHeadFresh: cache line state not CS_PENDING");
if ( mu_inP.mu_cn )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_s.mu_mState = mu_inP.mu_mCState;
mu_s.mu_co = mu_inP.mu_co;
}
switch ((int) mu_s.mu_mState) {
case mu_MS_HOME:
mu_line.mu_cState = (mu_inP.mu_co) ? (mu_CS_ONLY_FRESH) : (mu_CS_ONLY_DIRTY);
break;
case mu_MS_FRESH:
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_line.mu_cState = mu_CI_QUEUED_FRESH;
break;
case mu_MS_GONE:
if ( mu_s.mu_secondEntry )
{
mu_line.mu_cState = mu_CS_QUEUED_JUNK;
mu_line.mu_forwId = mu_inP.mu_forwId;
}
mu_AttachLists ( mu_i, mu_CC_COPY_VALID, mu_true, mu_inP, mu_s.mu_secondEntry, mu_exit, mu_aStatus );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_aStatus.mu_cState )) {
case mu_CT_HEAD_DIRTY:
mu_line.mu_cState = mu_CI_HEAD_DIRTY;
break;
case mu_CT_HEAD_CLEAN:
if ( !(mu_s.mu_co) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
if ( mu_POP_WASH )
{
Error.Error("Error: InvalidToHeadFresh: POP_WASH not implemented");
}
else
{
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CI_HEAD_CLEAN) : (mu_CI_HEAD_DIRTY);
}
break;
case mu_CT_TAIL_EXCL:
case mu_CT_HEAD_EXCL:
case mu_CT_MID_VALID:
case mu_CT_ONLYP_DIRTY:
case mu_CT_ONLY_DIRTY:
mu_line.mu_cState = mu_CI_HEAD_DIRTY;
break;
case mu_CT_HEAD_WASH:
if ( !(mu_s.mu_co) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_backId = mu_aStatus.mu_backId;
if ( mu_POP_WASH )
{
Error.Error("Error: InvalidToHeadFresh: POP_WASH not implemented");
}
else
{
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CI_HEAD_CLEAN) : (mu_CI_HEAD_DIRTY);
}
break;
case mu_CT_HEAD_FRESH:
case mu_CT_ONLY_FRESH:
if ( (mu_s.mu_mState) != (mu_MS_FRESH) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_cState = mu_CS_HEAD_FRESH;
break;
case mu_CT_TAIL_USED:
case mu_CT_HEAD_USED:
case mu_CT_HEAD_NEED:
case mu_CT_ONLY_USED:
mu_line.mu_cState = (mu_POP_QOLB) ? (mu_CI_HEADQ_DIRTY) : (mu_CI_HEAD_DIRTY);
break;
default:
Error.Error("Error: InvalidToHeadFresh: attach status not allowed");
break;
}
break;
default:
Error.Error("Error: InvalidToHeadFresh: memory state not allowed or not yet implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_HEAD_FRESH:
case mu_CS_HEAD_WASH:
case mu_CI_HEADQ_DIRTY:
case mu_CI_HEAD_DIRTY:
case mu_CI_HEAD_CLEAN:
case mu_CI_HW_WASH_HF:
case mu_CI_HD_WASH_HF:
case mu_CI_QUEUED_FRESH:
case mu_CS_ONLYP_DIRTY:
case mu_CS_ONLY_DIRTY:
case mu_CS_ONLY_FRESH:
break;
default:
Error.Error("Error: InvalidToHeadFresh: cache line state not allowed");
break;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_QueuedFreshToHeadFresh(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
/*** Variable declaration ***/
mu_1_AttachStatus mu_aStatus("aStatus",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CI_QUEUED_FRESH)) ) Error.Error("Assertion failed: QueuedFreshToHeadFresh: cache line state not allowed");
mu_line.mu_cState = mu_CS_QUEUED_FRESH;
}
mu_AttachLists ( mu_i, mu_CC_PEND_VALID, mu_false, mu_inP, mu_firstEntry, mu_exit, mu_aStatus );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_aStatus.mu_cState )) {
case mu_CT_HEAD_FRESH:
case mu_CT_ONLY_FRESH:
break;
default:
mu_CodeSetTStat ( mu_i, mu_TS_CTAG_STATE );
return ;
break;
}
mu_line.mu_cState = mu_CS_HEAD_FRESH;
}
};
/*** end procedure declaration ***/

void mu_OnlyFreshToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
bool mu__boolexpr59;
  if ((mu_line.mu_cState) == (mu_CS_ONLY_FRESH)) mu__boolexpr59 = TRUE ;
  else {
  mu__boolexpr59 = ((mu_line.mu_cState) == (mu_CI_OF_FLUSH_IN)) ; 
}
if ( !(mu__boolexpr59) ) Error.Error("Assertion failed: OnlyFreshToInvalid: cache line state not allowed");
mu_line.mu_cState = mu_CS_OF_retn_IN;
}
mu_OnlyFreshDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyFreshToInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_HeadFreshToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HeadFreshToInvalid: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_HEAD_FRESH)) ) Error.Error("Assertion failed: HeadFreshToInvalid: cache line state not CS_HEAD_FRESH");
mu_line.mu_cState = mu_CS_HX_FORW_HX;
}
mu_HeadFreshDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadFreshToInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_TailValidToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_TAIL_VALID:
break;
case mu_CS_TAIL_COPY:
if ( !(mu_POP_CLEAN) ) Error.Error("Assertion failed: TailValidToInvalid: POP_CLEAN false");
break;
default:
Error.Error("Error: TailValidToInvalid: cache line state not allowed");
break;
}
mu_line.mu_cState = mu_CS_TV_back_IN;
}
mu_TailValidDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
};
/*** end procedure declaration ***/

void mu_InvalidToHeadDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_MemoryCacheStates& mu_mState = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_mState;
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: InvalidToHeadDirty: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: InvalidToHeadDirty: cache line state not CS_INVALID");
}
mu_InvalidDoHeadDirty ( mu_i, mu_MC_CACHE_CLEAN, mu_true, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_mState) {
case mu_MS_HOME:
if ( !(!(mu_POP_CLEAN)) ) Error.Error("Assertion failed: InvalidToHeadDirty: POP_CLEAN true");
mu_line.mu_cState = mu_CI_ONLY_EXCL;
break;
case mu_MS_FRESH:
mu_line.mu_cState = mu_CI_QUEUED_CLEAN;
break;
case mu_MS_GONE:
break;
default:
Error.Error("Error: InvalidToHeadDirty: memory line state not allowed or not implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_QUEUED_CLEAN:
case mu_CI_HEADQ_DIRTY:
case mu_CI_HEAD_DIRTY:
case mu_CI_HEAD_CLEAN:
case mu_CI_ONLY_EXCL:
case mu_CI_ONLY_CLEAN:
break;
default:
Error.Error("Error: InvalidToHeadDirty: cache line state not allowed");
break;
}
mu_mState.undefine();
}
};
/*** end procedure declaration ***/

void mu_OnlyDirtyToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_ONLY_DIRTY:
if ( !(!(mu_POP_PAIR)) ) Error.Error("Assertion failed: OnlyDirtyToInvalid: POP_PAIR true");
break;
case mu_CI_OD_FLUSH_IN:
break;
case mu_CS_ONLYP_DIRTY:
if ( !(mu_POP_PAIR) ) Error.Error("Assertion failed: OnlyDirtyToInvalid: POP_PAIR false");
break;
case mu_CS_ONLY_USED:
case mu_CS_ONLYQ_DIRTY:
if ( !(mu_POP_QOLB) ) Error.Error("Assertion failed: OnlyDirtyToInvalid: POP_QOLB false");
break;
default:
Error.Error("Error: OnlyDirtyToInvalid: cache line state not allowed");
break;
}
}
mu_OnlyDirtyDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyDirtyToInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_HeadDirtyToInvalid(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HeadDirtyToInvalid: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CS_HEAD_DIRTY)) ) Error.Error("Assertion failed: HeadDirtyToInvalid: cache line state not CS_HEAD_DIRTY");
mu_line.mu_cState = mu_CS_HX_FORW_HX;
}
mu_HeadGoneDoInvalid ( mu_i, mu_SC_CREAD, mu_CC_NEXT_DHEAD, mu_false, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadDirtyToInvalid: cache line state not CS_INVALID");
}
};
/*** end procedure declaration ***/

void mu_QueuedCleanToHeadDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
/*** Variable declaration ***/
mu_1_AttachStatus mu_aStatus("aStatus",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: QueuedCleanToHeadDirty: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CI_QUEUED_CLEAN)) ) Error.Error("Assertion failed: QueuedCleanToHeadDirty: cache line state not CI_QUEUED_CLEAN");
mu_line.mu_cState = mu_CS_QUEUED_CLEAN;
}
mu_AttachLists ( mu_i, mu_CC_PEND_VALID, mu_false, mu_inP, mu_firstEntry, mu_exit, mu_aStatus );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_aStatus.mu_cState )) {
case mu_CT_HEAD_FRESH:
case mu_CT_ONLY_FRESH:
break;
default:
mu_CodeSetTStat ( mu_i, mu_TS_CTAG_STATE );
return ;
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_QUEUED_CLEAN:
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CS_HEAD_CLEAN) : (mu_CS_HEAD_DIRTY);
break;
case mu_CS_QUEUED_MODS:
Error.Error("Error: QueuedCleanToHeadDirty: POP_WEAK not implemented");
break;
default:
Error.Error("Error: QueuedCleanToHeadDirty: cache line state not allowed");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_ONLYP_DIRTY:
if ( !(mu_POP_PAIR) ) Error.Error("Assertion failed: QueuedCleanToHeadDirty: POP_PAIR false");
break;
case mu_CS_HEAD_DIRTY:
case mu_CS_HEAD_CLEAN:
case mu_CS_ONLY_DIRTY:
break;
default:
Error.Error("Error: QueuedCleanToHeadDirty: cache line state not allowed");
break;
}
}
};
/*** end procedure declaration ***/

void mu_OnlyFreshToOnlyDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
  mu_0_boolean& mu_cn = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_co;
if ( mu_firstEntry )
{
if ( !(mu_POP_MODS) ) Error.Error("Assertion failed: OnlyFreshToOnlyDirty: POP_MODS false");
if ( !((mu_line.mu_cState) == (mu_CS_ONLY_FRESH)) ) Error.Error("Assertion failed: OnlyFreshToOnlyDirty: cache line state not CS_ONLY_FRESH");
mu_line.mu_cState = mu_CS_OF_MODS_OD;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_GONE, mu_false );
mu_s.mu_secondEntry = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_secondEntry )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_OF_MODS_OD)) ) Error.Error("Assertion failed: OnlyFreshToOnlyDirty: cache line state not CS_OF_MODS_OD");
mu_cn = mu_inP.mu_cn;
}
if ( mu_cn )
{
if ( mu_s.mu_secondEntry )
{
mu_line.mu_cState = mu_CS_OF_retn_IN;
}
mu_OnlyFreshDoInvalid ( mu_i, mu_inP, mu_s.mu_secondEntry, mu_exit );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: OnlyFreshToOnlyDirty: cache line state not CS_INVALID");
mu_s.undefine();
return ;
}
if ( (mu_inP.mu_mCState) != (mu_MS_FRESH) )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CI_ONLY_CLEAN) : (mu_CI_ONLY_EXCL);
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_HeadFreshToHeadDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
  mu_1_MemoryCacheStates& mu_cState = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_mState;
  mu_0_boolean& mu_flag = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_co;
if ( mu_firstEntry )
{
if ( !(mu_POP_MODS) ) Error.Error("Assertion failed: HeadFreshToHeadDirty: POP_MODS false");
if ( !((mu_line.mu_cState) == (mu_CS_HEAD_FRESH)) ) Error.Error("Assertion failed: HeadFreshToHeadDirty: cache line state not CS_HEAD_FRESH");
mu_line.mu_cState = mu_CS_HF_MODS_HD;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_LIST_TO_GONE, mu_false );
mu_s.mu_secondEntry = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_secondEntry )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_cState = mu_line.mu_cState;
}
switch ((int) mu_cState) {
case mu_CS_HF_MODS_HD:
if ( mu_s.mu_secondEntry )
{
if ( mu_inP.mu_cn )
{
mu_line.mu_cState = mu_CS_HX_FORW_HX;
mu_flag = mu_true;
}
else
{
mu_line.mu_cState = mu_CI_HEAD_MODS;
mu_flag = mu_false;
}
}
if ( mu_flag )
{
mu_HeadFreshDoInvalid ( mu_i, mu_inP, mu_s.mu_secondEntry, mu_exit );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
}
break;
case mu_CS_OF_MODS_OD:
if ( mu_s.mu_secondEntry )
{
if ( mu_inP.mu_cn )
{
mu_line.mu_cState = mu_CS_OF_retn_IN;
mu_flag = mu_true;
}
else
{
mu_line.mu_cState = (mu_POP_CLEAN) ? (mu_CI_ONLY_CLEAN) : (mu_CI_ONLY_EXCL);
mu_flag = mu_false;
}
}
if ( mu_flag )
{
mu_OnlyFreshDoInvalid ( mu_i, mu_inP, mu_s.mu_secondEntry, mu_exit );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
}
break;
default:
Error.Error("Error: HeadFreshToHeadDirty: cache line state not allowed");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CS_INVALID:
case mu_CI_ONLY_CLEAN:
case mu_CI_ONLY_EXCL:
case mu_CI_HEAD_MODS:
break;
default:
Error.Error("Error: HeadFreshToHeadDirty: cache line state not allowed");
break;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_HeadDirtyToOnlyDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_ProcId& mu_nextId = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId;
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CI_HEAD_MODS)) ) Error.Error("Assertion failed: HeadDirtyToOnlyDirty: cache line state not CI_HEAD_MODS");
mu_line.mu_cState = mu_CS_HD_INVAL_OD;
mu_nextId = mu_line.mu_forwId;
}
mu_ListValidDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_HD_INVAL_OD)) ) Error.Error("Assertion failed: HeadDirtyToOnlyDirty: cache line state not CS_HD_INVAL_OD");
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
mu_nextId.undefine();
}
};
/*** end procedure declaration ***/

void mu_InvalidToOnlyDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
/*** Variable declaration ***/
mu_1_AttachStatus mu_aStatus("aStatus",0);

{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: InvalidToOnlyDirty: cache line state not CS_INVALID");
mu_line.mu_cState = mu_CS_PENDING;
mu_MemoryUpdateSrc ( mu_i, mu_SC_MREAD, mu_MC_CACHE_DIRTY, mu_true );
mu_s.mu_secondEntry = mu_true;
mu_exit = mu_true;
return ;
}
if ( mu_s.mu_secondEntry )
{
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_PENDING)) ) Error.Error("Assertion failed: InvalidToOnlyDirty: cache line state not CS_PENDING");
if ( mu_inP.mu_cn )
{
mu_CodeSetTStat ( mu_i, mu_TS_MTAG_STATE );
return ;
}
mu_s.mu_mState = mu_inP.mu_mCState;
}
switch ((int) mu_s.mu_mState) {
case mu_MS_HOME:
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
break;
case mu_MS_FRESH:
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_line.mu_cState = mu_CI_QUEUED_DIRTY;
break;
case mu_MS_GONE:
if ( mu_s.mu_secondEntry )
{
mu_line.mu_forwId = mu_inP.mu_forwId;
mu_line.mu_cState = mu_CS_QUEUED_JUNK;
}
mu_AttachLists ( mu_i, mu_CC_COPY_VALID, mu_true, mu_inP, mu_s.mu_secondEntry, mu_exit, mu_aStatus );
mu_s.mu_secondEntry = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_CSTATE_TYPES( mu_aStatus.mu_cState )) {
case mu_CT_HEAD_CLEAN:
case mu_CT_HEAD_WASH:
case mu_CT_TAIL_EXCL:
case mu_CT_HEAD_EXCL:
case mu_CT_HEAD_DIRTY:
case mu_CT_MID_VALID:
case mu_CT_ONLYP_DIRTY:
case mu_CT_ONLY_DIRTY:
mu_line.mu_cState = mu_CI_HEAD_MODS;
break;
case mu_CT_TAIL_USED:
case mu_CT_HEAD_USED:
case mu_CT_HEAD_NEED:
case mu_CT_ONLY_USED:
mu_line.mu_cState = (mu_POP_QOLB) ? (mu_CI_HEADQ_DIRTY) : (mu_CI_HEAD_MODS);
break;
default:
Error.Error("Error: InvalidToOnlyDirty: attach status not allowed");
break;
}
break;
default:
Error.Error("Error: InvalidToOnlyDirty: memory state not allowed or not yet implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_HEADQ_DIRTY:
case mu_CI_HEAD_MODS:
case mu_CI_QUEUED_DIRTY:
case mu_CS_ONLYP_DIRTY:
case mu_CS_ONLY_DIRTY:
break;
default:
Error.Error("Error: InvalidToOnlyDirty: cache line state not allowed");
break;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_QueuedDirtyToOnlyDirty(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CI_QUEUED_DIRTY)) ) Error.Error("Assertion failed: QueuedDirtyToOnlyDirty: cache line state not CI_QUEUED_DIRTY");
mu_line.mu_cState = mu_CS_QUEUED_DIRTY;
}
mu_ListFreshDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_QUEUED_DIRTY)) ) Error.Error("Assertion failed: QueuedDirtyToOnlyDirty: cache line state not CS_QUEUED_DIRTY");
if ( !(mu_CodeFault( mu_i )) )
{
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
}
}
};
/*** end procedure declaration ***/

void mu_QueuedDirtyToFlushed(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
  mu_0_boolean& mu_firstDo = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_secondEntry;
  mu_0_boolean& mu_firstEntrySub = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_co;
if ( mu_firstEntry )
{
if ( !((mu_line.mu_cState) == (mu_CI_QD_FLUSH_IN)) ) Error.Error("Assertion failed: QueuedDirtyToFlushed: cache line state not CI_QD_FLUSH_IN");
mu_line.mu_cState = mu_CS_QUEUED_DIRTY;
mu_firstDo = mu_true;
}
if ( mu_firstDo )
{
mu_ListFreshDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_QUEUED_DIRTY)) ) Error.Error("Assertion failed: QueuedDirtyToFlushed: cache line state not CS_QUEUED_DIRTY");
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_firstDo = mu_false;
mu_firstEntrySub = mu_true;
}
mu_OnlyDirtyDoInvalid ( mu_i, mu_inP, mu_firstEntrySub, mu_exit );
mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: QueuedDirtyToFlushed: cache line state not CS_INVALID");
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_HeadDirtyToFlushed(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_L0& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0;
  mu_0_boolean& mu_firstDo = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_secondEntry;
  mu_0_boolean& mu_firstEntrySub = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l0.mu_co;
  mu_1_ProcId& mu_nextId = mu_proc[mu_i].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId;
if ( mu_firstEntry )
{
if ( !(mu_POP_DIRTY) ) Error.Error("Assertion failed: HeadDirtyToFlushed: POP_DIRTY false");
if ( !((mu_line.mu_cState) == (mu_CI_HD_FLUSH_IN)) ) Error.Error("Assertion failed: HeadDirtyToFlushed: cache line state not CI_HD_FLUSH_IN");
mu_line.mu_cState = mu_CS_HX_INVAL_OX;
mu_firstDo = mu_true;
mu_nextId = mu_line.mu_forwId;
}
if ( mu_firstDo )
{
mu_ListValidDoInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_HX_INVAL_OX)) ) Error.Error("Assertion failed: HeadDirtyToFlushed: cache line state not CS_HX_INVAL_OX");
if ( mu_CodeFault( mu_i ) )
{
return ;
}
mu_firstDo = mu_false;
mu_firstEntrySub = mu_true;
}
mu_OnlyDirtyDoInvalid ( mu_i, mu_inP, mu_firstEntrySub, mu_exit );
mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
if ( !((mu_line.mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: HeadDirtyToFlushed: cache line state not CS_INVALID");
mu_s.undefine();
mu_nextId.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalRolloutEntry(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_LC& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lC;
if ( mu_firstEntry )
{
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CS_ONLY_DIRTY:
mu_OnlyDirtyToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_ONLY_FRESH:
mu_OnlyFreshToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_HEAD_DIRTY:
mu_HeadDirtyToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_HEAD_FRESH:
mu_HeadFreshToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_MID_VALID:
mu_MidValidToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_TAIL_VALID:
mu_TailValidToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
default:
Error.Error("Error: TypicalRolloutEntry: cache line state not allowed or not implemented");
break;
}
if ( mu_exit )
{
return ;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalFindLine(const mu_1_ProcId& mu_i, const mu_1_FindFlags& mu_flag, mu_1_ResPacket& mu_inP, const mu_1_MemoryId& mu_memId, const mu_1_MemoryLineId& mu_addrOffset, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_Cache& mu_cache = mu_proc[mu_i].mu_cache;
  mu_1_CacheLineId& mu_cTPtr = mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr;
  mu_1_LB& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lB;
  mu_0_boolean& mu_cacheMiss = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lB.mu_firstTo;
if ( mu_firstEntry )
{
mu_cTPtr = mu_CacheCheckSample( mu_i, mu_addrOffset, (int)mu_memId, mu_cTPtr );
bool mu__boolexpr60;
  if (!((mu_cache.mu_line[mu_cTPtr].mu_cState) == (mu_CS_INVALID))) mu__boolexpr60 = FALSE ;
  else {
  mu__boolexpr60 = ((mu_flag) == (mu_FF_FIND)) ; 
}
if ( mu__boolexpr60 )
{
mu_s.undefine();
return ;
}
mu_s.mu_cState = mu_cache.mu_line[mu_cTPtr].mu_cState;
bool mu__boolexpr61;
  if (mu_cache.mu_line[mu_cTPtr].mu_memId.isundefined()) mu__boolexpr61 = TRUE ;
  else {
bool mu__boolexpr62;
  if (!((mu_cache.mu_line[mu_cTPtr].mu_memId) == (mu_memId))) mu__boolexpr62 = FALSE ;
  else {
  mu__boolexpr62 = ((mu_cache.mu_line[mu_cTPtr].mu_addrOffset) == (mu_addrOffset)) ; 
}
  mu__boolexpr61 = (!(mu__boolexpr62)) ; 
}
mu_cacheMiss = mu__boolexpr61;
if (mu_memId.isundefined())
  mu_s.mu_memId.undefine();
else
  mu_s.mu_memId = mu_memId;
if (mu_addrOffset.isundefined())
  mu_s.mu_addrOffset.undefine();
else
  mu_s.mu_addrOffset = mu_addrOffset;
}
if ( mu_cacheMiss )
{
if ( (mu_s.mu_cState) != (mu_CS_INVALID) )
{
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
}
mu_cache.mu_line[mu_cTPtr].mu_memId = mu_s.mu_memId;
mu_cache.mu_line[mu_cTPtr].mu_addrOffset = mu_s.mu_addrOffset;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalLoadSetup(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
Error.Error("Error: TypicalLoadSetup: LOCAL cache line states not implemented");
break;
case mu_CS_INVALID:
break;
default:
if ( (mu_cacheUsage) == (mu_CU_LOCAL) )
{
Error.Error("Error: TypicalLoadSetup: only CU_GLOBAL cache usage implemented");
}
switch ((int) mu_line.mu_cState) {
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
case mu_CS_HEAD_FRESH:
case mu_CS_HEAD_DIRTY:
case mu_CS_ONLY_FRESH:
case mu_CS_ONLY_DIRTY:
break;
default:
Error.Error("Error: TypicalLoadSetup: cache line state not supported");
break;
}
break;
}
bool mu__boolexpr63;
  if ((mu_line.mu_cState) != (mu_CS_INVALID)) mu__boolexpr63 = TRUE ;
  else {
  mu__boolexpr63 = (mu_CodeFault( mu_i )) ; 
}
if ( mu__boolexpr63 )
{
return ;
}
}
if ( (mu_cacheUsage) == (mu_CU_LOCAL) )
{
Error.Error("Error: TypicalLoadSetup: only CU_GLOBAL cache usage implemented");
}
else
{
switch ((int) mu_proc[mu_i].mu_exec.mu_state.mu_fetchOption) {
case mu_CO_FETCH:
if ( mu_POP_FRESH )
{
mu_InvalidToHeadFresh ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
else
{
mu_InvalidToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
break;
case mu_CO_LOAD:
if ( mu_POP_DIRTY )
{
mu_InvalidToHeadDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
else
{
mu_InvalidToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
break;
case mu_CO_STORE:
mu_InvalidToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
default:
Error.Error("Error: TypicalLoadSetup: fetch option not yet implemented");
break;
}
}
}
};
/*** end procedure declaration ***/

void mu_TypicalLoad(const mu_1_ProcId& mu_i)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
Error.Error("Error: TypicalLoad: LOCAL cache line states not implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_READ_FRESH:
mu_line.mu_cState = mu_CS_INVALID;
break;
case mu_CI_HEAD_DIRTY:
mu_line.mu_cState = mu_CS_HEAD_DIRTY;
break;
case mu_CI_ONLY_EXCL:
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
break;
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
case mu_CI_HEAD_MODS:
case mu_CI_QUEUED_FRESH:
case mu_CI_QUEUED_CLEAN:
case mu_CI_QUEUED_DIRTY:
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
case mu_CS_HEAD_FRESH:
case mu_CS_ONLY_FRESH:
case mu_CS_HEAD_DIRTY:
case mu_CS_ONLY_DIRTY:
break;
default:
Error.Error("Error: TypicalLoad: cache line state not allowed");
break;
}
}
};
/*** end procedure declaration ***/

void mu_TypicalCleanup(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_LB& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lB;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_INVALID:
break;
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
case mu_CI_LD_FLUSH_IN:
Error.Error("Error: TypicalCleanup: LOCAL cache line states not implemented");
break;
default:
if ( !((mu_cacheUsage) == (mu_CU_GLOBAL)) ) Error.Error("Assertion failed: TypicalCleanup: only CU_GLOBAL cache usage implemented");
break;
}
mu_s.mu_cState = mu_line.mu_cState;
}
switch ((int) mu_s.mu_cState) {
case mu_CI_HEAD_MODS:
mu_HeadDirtyToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_QUEUED_DIRTY:
mu_QueuedDirtyToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_QUEUED_CLEAN:
mu_QueuedCleanToHeadDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_QUEUED_FRESH:
mu_QueuedFreshToHeadFresh ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_QD_FLUSH_IN:
mu_QueuedDirtyToFlushed ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_OD_FLUSH_IN:
mu_OnlyDirtyToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_OF_FLUSH_IN:
mu_OnlyFreshToInvalid ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CI_HD_FLUSH_IN:
mu_HeadDirtyToFlushed ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_INVALID:
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
case mu_CS_ONLY_FRESH:
case mu_CS_ONLY_DIRTY:
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
case mu_CS_HEAD_FRESH:
case mu_CS_HEAD_DIRTY:
break;
default:
Error.Error("Error: TypicalCleanup: cache line state not allowed or not yet implemented");
break;
}
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
return ;
}
switch ((int) mu_TypicalStableStates( mu_line.mu_cState )) {
case mu_SG_INVALID:
case mu_SG_GLOBAL:
break;
default:
Error.Error("Error: TypicalCleanup: cache line state not allowed or not yet implemented");
break;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalExecuteLoad(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_1_MemoryId& mu_memId, const mu_1_MemoryLineId& mu_addrOffset)
{
/*** Variable declaration ***/
mu_0_boolean mu_firstEntry("firstEntry",0);

/*** Variable declaration ***/
mu_0_boolean mu_exit("exit",2);

{
  mu_1_InstructionPhase& mu_insPhase = mu_proc[mu_i].mu_exec.mu_state.mu_insPhase;
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_firstEntry = mu_false;
mu_exit = mu_false;
if ( (mu_insPhase) == (mu_I_START) )
{
mu_insPhase = mu_I_ALLOCATE;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_ALLOCATE) )
{
mu_TypicalFindLine ( mu_i, mu_FF_WAIT, mu_inP, mu_memId, mu_addrOffset, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteLoad: CodeFault");
}
mu_insPhase = mu_I_SETUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_SETUP) )
{
mu_TypicalLoadSetup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteLoad: CodeFault");
}
mu_TypicalLoad ( mu_i );
mu_insPhase = mu_I_CLEANUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_CLEANUP) )
{
mu_TypicalCleanup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteLoad: CodeFault");
}
}
mu_state.undefine();
mu_state.mu_insType = mu_I_NONE;
}
};
/*** end procedure declaration ***/

void mu_TypicalExecuteDelete(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_1_MemoryId& mu_memId, const mu_1_MemoryLineId& mu_addrOffset)
{
/*** Variable declaration ***/
mu_0_boolean mu_firstEntry("firstEntry",0);

/*** Variable declaration ***/
mu_0_boolean mu_exit("exit",2);

{
  mu_1_InstructionPhase& mu_insPhase = mu_proc[mu_i].mu_exec.mu_state.mu_insPhase;
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
  mu_1__type_1& mu_line = mu_proc[mu_i].mu_cache.mu_line;
mu_firstEntry = mu_false;
mu_exit = mu_false;
if ( (mu_insPhase) == (mu_I_START) )
{
mu_insPhase = mu_I_ALLOCATE;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_ALLOCATE) )
{
mu_TypicalFindLine ( mu_i, mu_FF_FIND, mu_inP, mu_memId, mu_addrOffset, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteDelete: CodeFault");
}
if ( (mu_line[mu_state.mu_cTPtr].mu_cState) == (mu_CS_INVALID) )
{
mu_insPhase = mu_I_CLEANUP;
}
else
{
mu_insPhase = mu_I_SETUP;
mu_firstEntry = mu_true;
}
}
if ( (mu_insPhase) == (mu_I_SETUP) )
{
if ( mu_firstEntry )
{
if ( !((mu_line[mu_state.mu_cTPtr].mu_cState) != (mu_CS_INVALID)) ) Error.Error("Assertion failed: TypicalExecuteDelete: cache line state is CS_INVALID");
}
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteDelete: CodeFault");
}
}
if ( !((mu_line[mu_state.mu_cTPtr].mu_cState) == (mu_CS_INVALID)) ) Error.Error("Assertion failed: TypicalExecuteDelete: cache line state not CS_INVALID");
mu_state.undefine();
mu_state.mu_insType = mu_I_NONE;
}
};
/*** end procedure declaration ***/

void mu_TypicalStoreSetup(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_LB& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lB;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
Error.Error("Error: TypicalStoreSetup: LOCAL cache line states not implemented");
break;
case mu_CS_INVALID:
break;
default:
if ( (mu_cacheUsage) == (mu_CU_LOCAL) )
{
Error.Error("Error: TypicalStoreSetup: only CU_GLOBAL cache usage implemented");
}
break;
}
mu_s.mu_cState = mu_line.mu_cState;
mu_s.mu_firstTo = mu_true;
}
if ( mu_s.mu_firstTo )
{
switch ((int) mu_s.mu_cState) {
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_ONLY_FRESH:
if ( mu_POP_MODS )
{
mu_OnlyFreshToOnlyDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
else
{
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
break;
case mu_CS_HEAD_FRESH:
if ( mu_POP_MODS )
{
mu_HeadFreshToHeadDirty ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
else
{
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
}
break;
case mu_CS_HEAD_DIRTY:
case mu_CS_ONLY_DIRTY:
break;
case mu_CS_INVALID:
break;
default:
Error.Error("Error: TypicalStoreSetup: cache line state not allowed");
break;
}
if ( mu_exit )
{
return ;
}
bool mu__boolexpr64;
  if ((mu_line.mu_cState) != (mu_CS_INVALID)) mu__boolexpr64 = TRUE ;
  else {
  mu__boolexpr64 = (mu_CodeFault( mu_i )) ; 
}
if ( mu__boolexpr64 )
{
mu_s.undefine();
return ;
}
mu_s.mu_firstTo = mu_false;
mu_s.mu_firstEntrySub = mu_true;
}
if ( (mu_cacheUsage) == (mu_CU_LOCAL) )
{
Error.Error("Error: TypicalStoreSetup: only CU_GLOBAL cache usage implemented");
}
else
{
mu_InvalidToOnlyDirty ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalStore(const mu_1_ProcId& mu_i)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
Error.Error("Error: TypicalStore: LOCAL cache line states not implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_ONLY_CLEAN:
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
break;
case mu_CI_ONLY_EXCL:
case mu_CI_ONLY_DIRTY:
mu_line.mu_cState = mu_CS_ONLY_DIRTY;
break;
case mu_CS_HEAD_DIRTY:
mu_line.mu_cState = mu_CI_HEAD_MODS;
break;
case mu_CI_WRITE_CHECK:
case mu_CI_HEAD_MODS:
case mu_CI_QUEUED_DIRTY:
case mu_CS_ONLY_DIRTY:
break;
default:
Error.Error("Error: TypicalStore: cache line state not allowed");
break;
}
}
};
/*** end procedure declaration ***/

void mu_TypicalExecuteStore(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_1_MemoryId& mu_memId, const mu_1_MemoryLineId& mu_addrOffset)
{
/*** Variable declaration ***/
mu_0_boolean mu_firstEntry("firstEntry",0);

/*** Variable declaration ***/
mu_0_boolean mu_exit("exit",2);

{
  mu_1_InstructionPhase& mu_insPhase = mu_proc[mu_i].mu_exec.mu_state.mu_insPhase;
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
  mu_1__type_1& mu_line = mu_proc[mu_i].mu_cache.mu_line;
mu_firstEntry = mu_false;
mu_exit = mu_false;
if ( (mu_insPhase) == (mu_I_START) )
{
mu_insPhase = mu_I_ALLOCATE;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_ALLOCATE) )
{
mu_TypicalFindLine ( mu_i, mu_FF_WAIT, mu_inP, mu_memId, mu_addrOffset, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteStore: CodeFault");
}
mu_insPhase = mu_I_SETUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_SETUP) )
{
mu_TypicalStoreSetup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteStore: CodeFault");
}
if ( (mu_line[mu_state.mu_cTPtr].mu_cState) == (mu_CI_WRITE_CHECK) )
{
Error.Error("Error: TypicalExecuteStore: CI_WRITE_CHECK not implemented");
}
else
{
mu_TypicalStore ( mu_i );
mu_line[mu_state.mu_cTPtr].mu_data = mu_state.mu_data;
}
mu_insPhase = mu_I_CLEANUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_CLEANUP) )
{
mu_TypicalCleanup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteStore: CodeFault");
}
}
mu_state.undefine();
mu_state.mu_insType = mu_I_NONE;
}
};
/*** end procedure declaration ***/

void mu_TypicalFlushSetup(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_0_boolean& mu_firstEntry, mu_0_boolean& mu_exit)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
  mu_1_LB& mu_s = mu_proc[mu_i].mu_exec.mu_state.mu_subState.mu_lB;
if ( mu_firstEntry )
{
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
Error.Error("Error: TypicalFlushSetup: LOCAL cache line states not implemented");
break;
default:
if ( (mu_cacheUsage) == (mu_CU_LOCAL) )
{
Error.Error("Error: TypicalFlushSetup: only CU_GLOBAL cache usage implemented");
}
break;
}
mu_s.mu_cState = mu_line.mu_cState;
mu_s.mu_firstTo = mu_true;
}
if ( mu_s.mu_firstTo )
{
switch ((int) mu_s.mu_cState) {
case mu_CS_ONLY_FRESH:
case mu_CS_ONLY_DIRTY:
case mu_CS_HEAD_DIRTY:
break;
case mu_CS_TAIL_VALID:
case mu_CS_MID_VALID:
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_HEAD_FRESH:
mu_TypicalRolloutEntry ( mu_i, mu_inP, mu_firstEntry, mu_exit );
break;
case mu_CS_INVALID:
break;
default:
Error.Error("Error: TypicalFlushSetup: cache line state not allowed");
break;
}
if ( mu_exit )
{
return ;
}
bool mu__boolexpr65;
  if ((mu_line.mu_cState) != (mu_CS_INVALID)) mu__boolexpr65 = TRUE ;
  else {
  mu__boolexpr65 = (mu_CodeFault( mu_i )) ; 
}
if ( mu__boolexpr65 )
{
mu_s.undefine();
return ;
}
mu_s.mu_firstTo = mu_false;
mu_s.mu_firstEntrySub = mu_true;
}
mu_InvalidToOnlyDirty ( mu_i, mu_inP, mu_s.mu_firstEntrySub, mu_exit );
mu_s.mu_firstEntrySub = mu_false;
if ( mu_exit )
{
return ;
}
mu_s.undefine();
}
};
/*** end procedure declaration ***/

void mu_TypicalFlush(const mu_1_ProcId& mu_i)
{
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
switch ((int) mu_line.mu_cState) {
case mu_CS_LOCAL_DIRTY:
case mu_CS_LOCAL_CLEAN:
case mu_CS_INVALID:
Error.Error("Error: TypicalFlush: CU_LOCAL not implemented");
break;
}
switch ((int) mu_line.mu_cState) {
case mu_CI_QUEUED_DIRTY:
mu_line.mu_cState = mu_CI_QD_FLUSH_IN;
break;
case mu_CI_ONLY_EXCL:
case mu_CS_ONLY_DIRTY:
mu_line.mu_cState = mu_CI_OD_FLUSH_IN;
break;
case mu_CS_ONLY_FRESH:
mu_line.mu_cState = mu_CI_OF_FLUSH_IN;
break;
case mu_CI_HEAD_MODS:
case mu_CI_HEAD_DIRTY:
case mu_CS_HEAD_DIRTY:
mu_line.mu_cState = mu_CI_HD_FLUSH_IN;
break;
case mu_CS_INVALID:
break;
default:
Error.Error("Error: TypicalFlush: cache line state not allowed or not implemented");
break;
}
}
};
/*** end procedure declaration ***/

void mu_TypicalExecuteFlush(const mu_1_ProcId& mu_i, mu_1_ResPacket& mu_inP, const mu_1_MemoryId& mu_memId, const mu_1_MemoryLineId& mu_addrOffset)
{
/*** Variable declaration ***/
mu_0_boolean mu_firstEntry("firstEntry",0);

/*** Variable declaration ***/
mu_0_boolean mu_exit("exit",2);

{
  mu_1_InstructionPhase& mu_insPhase = mu_proc[mu_i].mu_exec.mu_state.mu_insPhase;
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_firstEntry = mu_false;
mu_exit = mu_false;
if ( (mu_insPhase) == (mu_I_START) )
{
mu_insPhase = mu_I_ALLOCATE;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_ALLOCATE) )
{
if ( mu_firstEntry )
{
if ( !((mu_cacheUsage) == (mu_CU_GLOBAL)) ) Error.Error("Assertion failed: TypicalExecuteFlush: only CU_GLOBAL cache usage implemented");
}
mu_TypicalFindLine ( mu_i, mu_FF_WAIT, mu_inP, mu_memId, mu_addrOffset, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteFlush: CodeFault");
}
mu_insPhase = mu_I_SETUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_SETUP) )
{
mu_TypicalFlushSetup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteFlush: CodeFault");
}
mu_TypicalFlush ( mu_i );
mu_insPhase = mu_I_CLEANUP;
mu_firstEntry = mu_true;
}
if ( (mu_insPhase) == (mu_I_CLEANUP) )
{
mu_TypicalCleanup ( mu_i, mu_inP, mu_firstEntry, mu_exit );
if ( mu_exit )
{
return ;
}
if ( mu_CodeFault( mu_i ) )
{
Error.Error("Error: TypicalExecuteFlush: CodeFault");
}
}
mu_state.undefine();
mu_state.mu_insType = mu_I_NONE;
}
};
/*** end procedure declaration ***/





/********************
  The world
 ********************/
void world_class::clear()
{
  mu_cacheUsage.clear();
  mu_proc.clear();
  mu_memory.clear();
}
void world_class::undefine()
{
  mu_cacheUsage.undefine();
  mu_proc.undefine();
  mu_memory.undefine();
}
void world_class::reset()
{
  mu_cacheUsage.reset();
  mu_proc.reset();
  mu_memory.reset();
}
void world_class::print()
{
  static int num_calls = 0; /* to ward off recursive calls. */
  if ( num_calls == 0 ) {
    num_calls++;
  mu_cacheUsage.print();
  mu_proc.print();
  mu_memory.print();
    num_calls--;
}
}
void world_class::print_statistic()
{
  static int num_calls = 0; /* to ward off recursive calls. */
  if ( num_calls == 0 ) {
    num_calls++;
  mu_cacheUsage.print_statistic();
  mu_proc.print_statistic();
  mu_memory.print_statistic();
    num_calls--;
}
}
void world_class::print_diff( state *prevstate )
{
  if ( prevstate != NULL )
  {
    mu_cacheUsage.print_diff(prevstate);
    mu_proc.print_diff(prevstate);
    mu_memory.print_diff(prevstate);
  }
  else
print();
}
void world_class::to_state(state *newstate)
{
  mu_cacheUsage.to_state( newstate );
  mu_proc.to_state( newstate );
  mu_memory.to_state( newstate );
}
void world_class::setstate(state *thestate)
{
}


/********************
  Rule declarations
 ********************/
/******************** RuleBase0 ********************/
class RuleBase0
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("continue instructions, i:%s", mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr66;
  if (!((mu_proc[mu_i].mu_exec.mu_state.mu_insType) != (mu_I_NONE))) mu__boolexpr66 = FALSE ;
  else {
  mu__boolexpr66 = (!(mu_proc[mu_i].mu_exec.mu_resPacket.mu_cn.isundefined())) ; 
}
    return mu__boolexpr66;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 0;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 2 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr67;
  if (!((mu_proc[mu_i].mu_exec.mu_state.mu_insType) != (mu_I_NONE))) mu__boolexpr67 = FALSE ;
  else {
  mu__boolexpr67 = (!(mu_proc[mu_i].mu_exec.mu_resPacket.mu_cn.isundefined())) ; 
}
	      if (mu__boolexpr67) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 0;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_MemoryId mu_m("m",0);

/*** Variable declaration ***/
mu_1_MemoryLineId mu_o("o",1);

{
  mu_1_ResPacket& mu_inP = mu_proc[mu_i].mu_exec.mu_resPacket;
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_proc[mu_i].mu_exec.mu_state.mu_cTPtr];
mu_m.undefine();
mu_o.undefine();
if ( (mu_inP.mu_cmd) == (mu_SC_RESP64) )
{
mu_line.mu_data = mu_inP.mu_data;
}
switch ((int) mu_proc[mu_i].mu_exec.mu_state.mu_insType) {
case mu_I_LOAD:
mu_TypicalExecuteLoad ( mu_i, mu_inP, mu_m, mu_o );
break;
case mu_I_DELETE:
mu_TypicalExecuteDelete ( mu_i, mu_inP, mu_m, mu_o );
break;
case mu_I_STORE:
mu_TypicalExecuteStore ( mu_i, mu_inP, mu_m, mu_o );
break;
case mu_I_FLUSH:
mu_TypicalExecuteFlush ( mu_i, mu_inP, mu_m, mu_o );
break;
default:
Error.Error("Error: continue instructions: instruction not yet implemented");
break;
}
mu_RemoveResPacket ( mu_inP );
mu_UndefineUnusedValues (  );
}
  };

};
/******************** RuleBase1 ********************/
class RuleBase1
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("flush instruction, k:%s, o:%s, m:%s, i:%s", mu_k.Name(), mu_o.Name(), mu_m.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr68;
bool mu__boolexpr69;
  if (!(mu_EN_FLUSH)) mu__boolexpr69 = FALSE ;
  else {
  mu__boolexpr69 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr69)) mu__boolexpr68 = FALSE ;
  else {
bool mu__boolexpr70;
bool mu__quant71; 
mu__quant71 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr72;
bool mu__boolexpr73;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr73 = FALSE ;
  else {
  mu__boolexpr73 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr73)) mu__boolexpr72 = FALSE ;
  else {
  mu__boolexpr72 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr72) )
  { mu__quant71 = TRUE; break; }
};
};
  if (!(mu__quant71)) mu__boolexpr70 = TRUE ;
  else {
bool mu__boolexpr74;
bool mu__boolexpr75;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr75 = FALSE ;
  else {
  mu__boolexpr75 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr75)) mu__boolexpr74 = FALSE ;
  else {
  mu__boolexpr74 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr70 = (mu__boolexpr74) ; 
}
  mu__boolexpr68 = (mu__boolexpr70) ; 
}
    return mu__boolexpr68;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 2;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 4 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr76;
bool mu__boolexpr77;
  if (!(mu_EN_FLUSH)) mu__boolexpr77 = FALSE ;
  else {
  mu__boolexpr77 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr77)) mu__boolexpr76 = FALSE ;
  else {
bool mu__boolexpr78;
bool mu__quant79; 
mu__quant79 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr80;
bool mu__boolexpr81;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr81 = FALSE ;
  else {
  mu__boolexpr81 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr81)) mu__boolexpr80 = FALSE ;
  else {
  mu__boolexpr80 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr80) )
  { mu__quant79 = TRUE; break; }
};
};
  if (!(mu__quant79)) mu__boolexpr78 = TRUE ;
  else {
bool mu__boolexpr82;
bool mu__boolexpr83;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr83 = FALSE ;
  else {
  mu__boolexpr83 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr83)) mu__boolexpr82 = FALSE ;
  else {
  mu__boolexpr82 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr78 = (mu__boolexpr82) ; 
}
  mu__boolexpr76 = (mu__boolexpr78) ; 
}
	      if (mu__boolexpr76) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 2;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_ResPacket mu_p("p",0);

{
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_p.undefine();
mu_state.undefine();
mu_state.mu_insType = mu_I_FLUSH;
mu_state.mu_insPhase = mu_I_START;
mu_state.mu_cTPtr = mu_k;
mu_state.mu_tStat = mu_TS_NORM_CODE;
mu_TypicalExecuteFlush ( mu_i, mu_p, mu_m, mu_o );
mu_UndefineUnusedValues (  );
}
  };

};
/******************** RuleBase2 ********************/
class RuleBase2
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("store instruction, d:%s, k:%s, o:%s, m:%s, i:%s", mu_d.Name(), mu_k.Name(), mu_o.Name(), mu_m.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr84;
bool mu__boolexpr85;
  if (!(mu_EN_STORE)) mu__boolexpr85 = FALSE ;
  else {
  mu__boolexpr85 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr85)) mu__boolexpr84 = FALSE ;
  else {
bool mu__boolexpr86;
bool mu__quant87; 
mu__quant87 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr88;
bool mu__boolexpr89;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr89 = FALSE ;
  else {
  mu__boolexpr89 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr89)) mu__boolexpr88 = FALSE ;
  else {
  mu__boolexpr88 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr88) )
  { mu__quant87 = TRUE; break; }
};
};
  if (!(mu__quant87)) mu__boolexpr86 = TRUE ;
  else {
bool mu__boolexpr90;
bool mu__boolexpr91;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr91 = FALSE ;
  else {
  mu__boolexpr91 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr91)) mu__boolexpr90 = FALSE ;
  else {
  mu__boolexpr90 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr86 = (mu__boolexpr90) ; 
}
  mu__boolexpr84 = (mu__boolexpr86) ; 
}
    return mu__boolexpr84;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 4;
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 6 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr92;
bool mu__boolexpr93;
  if (!(mu_EN_STORE)) mu__boolexpr93 = FALSE ;
  else {
  mu__boolexpr93 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr93)) mu__boolexpr92 = FALSE ;
  else {
bool mu__boolexpr94;
bool mu__quant95; 
mu__quant95 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr96;
bool mu__boolexpr97;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr97 = FALSE ;
  else {
  mu__boolexpr97 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr97)) mu__boolexpr96 = FALSE ;
  else {
  mu__boolexpr96 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr96) )
  { mu__quant95 = TRUE; break; }
};
};
  if (!(mu__quant95)) mu__boolexpr94 = TRUE ;
  else {
bool mu__boolexpr98;
bool mu__boolexpr99;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr99 = FALSE ;
  else {
  mu__boolexpr99 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr99)) mu__boolexpr98 = FALSE ;
  else {
  mu__boolexpr98 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr94 = (mu__boolexpr98) ; 
}
  mu__boolexpr92 = (mu__boolexpr94) ; 
}
	      if (mu__boolexpr92) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 4;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_ResPacket mu_p("p",0);

{
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_p.undefine();
mu_state.undefine();
mu_state.mu_insType = mu_I_STORE;
mu_state.mu_insPhase = mu_I_START;
mu_state.mu_cTPtr = mu_k;
mu_state.mu_tStat = mu_TS_NORM_CODE;
mu_state.mu_data = mu_d;
mu_TypicalExecuteStore ( mu_i, mu_p, mu_m, mu_o );
mu_UndefineUnusedValues (  );
}
  };

};
/******************** RuleBase3 ********************/
class RuleBase3
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("delete instruction, k:%s, o:%s, m:%s, i:%s", mu_k.Name(), mu_o.Name(), mu_m.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr100;
bool mu__boolexpr101;
  if (!(mu_EN_DELETE)) mu__boolexpr101 = FALSE ;
  else {
  mu__boolexpr101 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr101)) mu__boolexpr100 = FALSE ;
  else {
bool mu__boolexpr102;
bool mu__quant103; 
mu__quant103 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr104;
bool mu__boolexpr105;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr105 = FALSE ;
  else {
  mu__boolexpr105 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr105)) mu__boolexpr104 = FALSE ;
  else {
  mu__boolexpr104 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr104) )
  { mu__quant103 = TRUE; break; }
};
};
  if (!(mu__quant103)) mu__boolexpr102 = TRUE ;
  else {
bool mu__boolexpr106;
bool mu__boolexpr107;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr107 = FALSE ;
  else {
  mu__boolexpr107 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr107)) mu__boolexpr106 = FALSE ;
  else {
  mu__boolexpr106 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr102 = (mu__boolexpr106) ; 
}
  mu__boolexpr100 = (mu__boolexpr102) ; 
}
    return mu__boolexpr100;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 6;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 8 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr108;
bool mu__boolexpr109;
  if (!(mu_EN_DELETE)) mu__boolexpr109 = FALSE ;
  else {
  mu__boolexpr109 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr109)) mu__boolexpr108 = FALSE ;
  else {
bool mu__boolexpr110;
bool mu__quant111; 
mu__quant111 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr112;
bool mu__boolexpr113;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr113 = FALSE ;
  else {
  mu__boolexpr113 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr113)) mu__boolexpr112 = FALSE ;
  else {
  mu__boolexpr112 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr112) )
  { mu__quant111 = TRUE; break; }
};
};
  if (!(mu__quant111)) mu__boolexpr110 = TRUE ;
  else {
bool mu__boolexpr114;
bool mu__boolexpr115;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr115 = FALSE ;
  else {
  mu__boolexpr115 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr115)) mu__boolexpr114 = FALSE ;
  else {
  mu__boolexpr114 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr110 = (mu__boolexpr114) ; 
}
  mu__boolexpr108 = (mu__boolexpr110) ; 
}
	      if (mu__boolexpr108) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 6;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_ResPacket mu_p("p",0);

{
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_p.undefine();
mu_state.undefine();
mu_state.mu_insType = mu_I_DELETE;
mu_state.mu_insPhase = mu_I_START;
mu_state.mu_cTPtr = mu_k;
mu_state.mu_tStat = mu_TS_NORM_CODE;
mu_TypicalExecuteDelete ( mu_i, mu_p, mu_m, mu_o );
mu_UndefineUnusedValues (  );
}
  };

};
/******************** RuleBase4 ********************/
class RuleBase4
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_FetchOptions mu_fo;
    mu_fo.value((r % 3) + 256);
    r = r / 3;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("load instruction, fo:%s, k:%s, o:%s, m:%s, i:%s", mu_fo.Name(), mu_k.Name(), mu_o.Name(), mu_m.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_FetchOptions mu_fo;
    mu_fo.value((r % 3) + 256);
    r = r / 3;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr116;
bool mu__boolexpr117;
bool mu__boolexpr118;
bool mu__boolexpr119;
bool mu__boolexpr120;
  if (!(mu_EN_LOAD)) mu__boolexpr120 = FALSE ;
  else {
bool mu__boolexpr121;
  if (!((mu_fo) == (mu_CO_FETCH))) mu__boolexpr121 = TRUE ;
  else {
  mu__boolexpr121 = (mu_FO_FETCH) ; 
}
  mu__boolexpr120 = (mu__boolexpr121) ; 
}
  if (!(mu__boolexpr120)) mu__boolexpr119 = FALSE ;
  else {
bool mu__boolexpr122;
  if (!((mu_fo) == (mu_CO_LOAD))) mu__boolexpr122 = TRUE ;
  else {
  mu__boolexpr122 = (mu_FO_LOAD) ; 
}
  mu__boolexpr119 = (mu__boolexpr122) ; 
}
  if (!(mu__boolexpr119)) mu__boolexpr118 = FALSE ;
  else {
bool mu__boolexpr123;
  if (!((mu_fo) == (mu_CO_STORE))) mu__boolexpr123 = TRUE ;
  else {
  mu__boolexpr123 = (mu_FO_STORE) ; 
}
  mu__boolexpr118 = (mu__boolexpr123) ; 
}
  if (!(mu__boolexpr118)) mu__boolexpr117 = FALSE ;
  else {
  mu__boolexpr117 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr117)) mu__boolexpr116 = FALSE ;
  else {
bool mu__boolexpr124;
bool mu__quant125; 
mu__quant125 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr126;
bool mu__boolexpr127;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr127 = FALSE ;
  else {
  mu__boolexpr127 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr127)) mu__boolexpr126 = FALSE ;
  else {
  mu__boolexpr126 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr126) )
  { mu__quant125 = TRUE; break; }
};
};
  if (!(mu__quant125)) mu__boolexpr124 = TRUE ;
  else {
bool mu__boolexpr128;
bool mu__boolexpr129;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr129 = FALSE ;
  else {
  mu__boolexpr129 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr129)) mu__boolexpr128 = FALSE ;
  else {
  mu__boolexpr128 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr124 = (mu__boolexpr128) ; 
}
  mu__boolexpr116 = (mu__boolexpr124) ; 
}
    return mu__boolexpr116;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 8;
    static mu_1_FetchOptions mu_fo;
    mu_fo.value((r % 3) + 256);
    r = r / 3;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 14 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr130;
bool mu__boolexpr131;
bool mu__boolexpr132;
bool mu__boolexpr133;
bool mu__boolexpr134;
  if (!(mu_EN_LOAD)) mu__boolexpr134 = FALSE ;
  else {
bool mu__boolexpr135;
  if (!((mu_fo) == (mu_CO_FETCH))) mu__boolexpr135 = TRUE ;
  else {
  mu__boolexpr135 = (mu_FO_FETCH) ; 
}
  mu__boolexpr134 = (mu__boolexpr135) ; 
}
  if (!(mu__boolexpr134)) mu__boolexpr133 = FALSE ;
  else {
bool mu__boolexpr136;
  if (!((mu_fo) == (mu_CO_LOAD))) mu__boolexpr136 = TRUE ;
  else {
  mu__boolexpr136 = (mu_FO_LOAD) ; 
}
  mu__boolexpr133 = (mu__boolexpr136) ; 
}
  if (!(mu__boolexpr133)) mu__boolexpr132 = FALSE ;
  else {
bool mu__boolexpr137;
  if (!((mu_fo) == (mu_CO_STORE))) mu__boolexpr137 = TRUE ;
  else {
  mu__boolexpr137 = (mu_FO_STORE) ; 
}
  mu__boolexpr132 = (mu__boolexpr137) ; 
}
  if (!(mu__boolexpr132)) mu__boolexpr131 = FALSE ;
  else {
  mu__boolexpr131 = ((mu_proc[mu_i].mu_exec.mu_state.mu_insType) == (mu_I_NONE)) ; 
}
  if (!(mu__boolexpr131)) mu__boolexpr130 = FALSE ;
  else {
bool mu__boolexpr138;
bool mu__quant139; 
mu__quant139 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr140;
bool mu__boolexpr141;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr141 = FALSE ;
  else {
  mu__boolexpr141 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr141)) mu__boolexpr140 = FALSE ;
  else {
  mu__boolexpr140 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_m)) ; 
}
if ( (mu__boolexpr140) )
  { mu__quant139 = TRUE; break; }
};
};
  if (!(mu__quant139)) mu__boolexpr138 = TRUE ;
  else {
bool mu__boolexpr142;
bool mu__boolexpr143;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr143 = FALSE ;
  else {
  mu__boolexpr143 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_o)) ; 
}
  if (!(mu__boolexpr143)) mu__boolexpr142 = FALSE ;
  else {
  mu__boolexpr142 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_m)) ; 
}
  mu__boolexpr138 = (mu__boolexpr142) ; 
}
  mu__boolexpr130 = (mu__boolexpr138) ; 
}
	      if (mu__boolexpr130) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 8;
    mu_fo.value((r % 3) + 256);
    r = r / 3;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_FetchOptions mu_fo;
    mu_fo.value((r % 3) + 256);
    r = r / 3;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_MemoryLineId mu_o;
    mu_o.value((r % 1) + 4);
    r = r / 1;
    static mu_1_MemoryId mu_m;
    mu_m.value((r % 1) + 3);
    r = r / 1;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_ResPacket mu_p("p",0);

{
  mu_1_ExecState& mu_state = mu_proc[mu_i].mu_exec.mu_state;
mu_p.undefine();
mu_state.undefine();
mu_state.mu_insType = mu_I_LOAD;
mu_state.mu_insPhase = mu_I_START;
mu_state.mu_cTPtr = mu_k;
mu_state.mu_tStat = mu_TS_NORM_CODE;
mu_state.mu_fetchOption = mu_fo;
mu_TypicalExecuteLoad ( mu_i, mu_p, mu_m, mu_o );
mu_UndefineUnusedValues (  );
}
  };

};
/******************** RuleBase5 ********************/
class RuleBase5
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    return tsprintf("cache behavior, k:%s, j:%s, i:%s", mu_k.Name(), mu_j.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
bool mu__boolexpr144;
bool mu__boolexpr145;
bool mu__boolexpr146;
  if (!(!(mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId.isundefined()))) mu__boolexpr146 = FALSE ;
  else {
  mu__boolexpr146 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId>=1 && mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId<=2)) ; 
}
  if (!(mu__boolexpr146)) mu__boolexpr145 = FALSE ;
  else {
  mu__boolexpr145 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId) == (mu_i)) ; 
}
  if (!(mu__boolexpr145)) mu__boolexpr144 = FALSE ;
  else {
bool mu__boolexpr147;
bool mu__quant148; 
mu__quant148 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr149;
bool mu__boolexpr150;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr150 = FALSE ;
  else {
  mu__boolexpr150 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_offset)) ; 
}
  if (!(mu__boolexpr150)) mu__boolexpr149 = FALSE ;
  else {
  mu__boolexpr149 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_memId)) ; 
}
if ( (mu__boolexpr149) )
  { mu__quant148 = TRUE; break; }
};
};
  if (!(mu__quant148)) mu__boolexpr147 = TRUE ;
  else {
bool mu__boolexpr151;
bool mu__boolexpr152;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr152 = FALSE ;
  else {
  mu__boolexpr152 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_offset)) ; 
}
  if (!(mu__boolexpr152)) mu__boolexpr151 = FALSE ;
  else {
  mu__boolexpr151 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_memId)) ; 
}
  mu__boolexpr147 = (mu__boolexpr151) ; 
}
  mu__boolexpr144 = (mu__boolexpr147) ; 
}
    return mu__boolexpr144;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 14;
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    while (what_rule < 18 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr153;
bool mu__boolexpr154;
bool mu__boolexpr155;
  if (!(!(mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId.isundefined()))) mu__boolexpr155 = FALSE ;
  else {
  mu__boolexpr155 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId>=1 && mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId<=2)) ; 
}
  if (!(mu__boolexpr155)) mu__boolexpr154 = FALSE ;
  else {
  mu__boolexpr154 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId) == (mu_i)) ; 
}
  if (!(mu__boolexpr154)) mu__boolexpr153 = FALSE ;
  else {
bool mu__boolexpr156;
bool mu__quant157; 
mu__quant157 = FALSE;
{
for(int mu_l = 5; mu_l <= 5; mu_l++) {
bool mu__boolexpr158;
bool mu__boolexpr159;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_cState) != (mu_CS_INVALID))) mu__boolexpr159 = FALSE ;
  else {
  mu__boolexpr159 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_addrOffset) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_offset)) ; 
}
  if (!(mu__boolexpr159)) mu__boolexpr158 = FALSE ;
  else {
  mu__boolexpr158 = ((mu_proc[mu_i].mu_cache.mu_line[mu_l].mu_memId) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_memId)) ; 
}
if ( (mu__boolexpr158) )
  { mu__quant157 = TRUE; break; }
};
};
  if (!(mu__quant157)) mu__boolexpr156 = TRUE ;
  else {
bool mu__boolexpr160;
bool mu__boolexpr161;
  if (!((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr161 = FALSE ;
  else {
  mu__boolexpr161 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_offset)) ; 
}
  if (!(mu__boolexpr161)) mu__boolexpr160 = FALSE ;
  else {
  mu__boolexpr160 = ((mu_proc[mu_i].mu_cache.mu_line[mu_k].mu_memId) == (mu_proc[mu_j].mu_exec.mu_reqPacket.mu_memId)) ; 
}
  mu__boolexpr156 = (mu__boolexpr160) ; 
}
  mu__boolexpr153 = (mu__boolexpr156) ; 
}
	      if (mu__boolexpr153) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 14;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    mu_i.value((r % 2) + 1);
    r = r / 2;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_CacheLineId mu_k;
    mu_k.value((r % 1) + 5);
    r = r / 1;
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_ProcId mu_i;
    mu_i.value((r % 2) + 1);
    r = r / 2;
/*** Variable declaration ***/
mu_1_ResPacket mu_outP("outP",0);

/*** Variable declaration ***/
mu_1_CacheLineId mu_c("c",19);

/*** Variable declaration ***/
mu_1_DataFlags mu_updates("updates",20);

{
  mu_1_ReqPacket& mu_inP = mu_proc[mu_j].mu_exec.mu_reqPacket;
mu_outP.undefine();
switch ((int) mu_inP.mu_cmd) {
case mu_SC_CREAD:
break;
default:
Error.Error("Error: cache behavior: transaction command not implemented");
break;
}
mu_c = mu_CacheCheckSample( mu_i, mu_inP.mu_offset, mu_inP.mu_memId, mu_k );
{
  mu_1_CacheLine& mu_line = mu_proc[mu_i].mu_cache.mu_line[mu_c];
mu_outP.mu_mCState = mu_line.mu_cState;
mu_outP.mu_cmd = mu_SC_RESP00;
if ( (mu_CSTATE_TYPES( mu_line.mu_cState )) == (mu_CT_TAIL_USED) )
{
if ( !(mu_line.mu_backId.isundefined()) )
{
mu_outP.mu_forwId = mu_line.mu_backId;
}
}
else
{
if ( !(mu_line.mu_forwId.isundefined()) )
{
mu_outP.mu_forwId = mu_line.mu_forwId;
}
}
if ( !(mu_line.mu_backId.isundefined()) )
{
mu_outP.mu_backId = mu_line.mu_backId;
}
bool mu__boolexpr162;
  if ((mu_line.mu_cState) == (mu_CS_INVALID)) mu__boolexpr162 = TRUE ;
  else {
bool mu__boolexpr163;
  if (!((mu_line.mu_memId) == (mu_inP.mu_memId))) mu__boolexpr163 = FALSE ;
  else {
  mu__boolexpr163 = ((mu_line.mu_addrOffset) == (mu_inP.mu_offset)) ; 
}
  mu__boolexpr162 = (!(mu__boolexpr163)) ; 
}
if ( mu__boolexpr162 )
{
mu_outP.mu_cn = mu_true;
mu_outP.mu_mCState = mu_CS_INVALID;
}
else
{
mu_updates = mu_CacheTagUpdate( mu_line, mu_inP );
switch ((int) mu_inP.mu_cmd) {
case mu_SC_CREAD:
if ( (mu_updates) == (mu_NORM_DATA) )
{
if ( !(mu_line.mu_data.isundefined()) )
{
mu_outP.mu_data = mu_line.mu_data;
}
mu_outP.mu_cmd = mu_SC_RESP64;
}
break;
default:
Error.Error("Error: cache behavior: transaction command not implemented");
break;
}
switch ((int) mu_updates) {
case mu_NORM_DATA:
mu_outP.mu_cn = mu_false;
mu_outP.mu_cmd = mu_SC_RESP64;
break;
case mu_NORM_NONE:
mu_outP.mu_cn = mu_false;
mu_outP.mu_cmd = mu_SC_RESP00;
break;
case mu_NORM_NULL:
mu_outP.mu_cn = mu_true;
mu_outP.mu_cmd = mu_SC_RESP00;
break;
case mu_NORM_SKIP:
mu_outP.mu_cn = mu_true;
break;
default:
Error.Error("Error: cache behavior: CacheTagUpdate return value not implemented");
break;
}
}
mu_SendResPacket ( mu_outP, (int)mu_inP.mu_sourceId );
mu_RemoveReqPacket ( mu_inP );
mu_UndefineUnusedValues (  );
}
}
  };

};
/******************** RuleBase6 ********************/
class RuleBase6
{
public:
  int Priority()
  {
    return 0;
  }
  char * Name(unsigned r)
  {
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_MemoryId mu_i;
    mu_i.value((r % 1) + 3);
    r = r / 1;
    return tsprintf("memory behavior, j:%s, i:%s", mu_j.Name(), mu_i.Name());
  }
  bool Condition(unsigned r)
  {
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_MemoryId mu_i;
    mu_i.value((r % 1) + 3);
    r = r / 1;
bool mu__boolexpr164;
bool mu__boolexpr165;
  if (!(!(mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId.isundefined()))) mu__boolexpr165 = FALSE ;
  else {
  mu__boolexpr165 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId>=3 && mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId<=3)) ; 
}
  if (!(mu__boolexpr165)) mu__boolexpr164 = FALSE ;
  else {
  mu__boolexpr164 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId) == (mu_i)) ; 
}
    return mu__boolexpr164;
  }

  void NextRule(unsigned & what_rule)
  {
    unsigned r = what_rule - 18;
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_MemoryId mu_i;
    mu_i.value((r % 1) + 3);
    r = r / 1;
    while (what_rule < 20 )
      {
	if ( ( TRUE  ) ) {
bool mu__boolexpr166;
bool mu__boolexpr167;
  if (!(!(mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId.isundefined()))) mu__boolexpr167 = FALSE ;
  else {
  mu__boolexpr167 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId>=3 && mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId<=3)) ; 
}
  if (!(mu__boolexpr167)) mu__boolexpr166 = FALSE ;
  else {
  mu__boolexpr166 = ((mu_proc[mu_j].mu_exec.mu_reqPacket.mu_targetId) == (mu_i)) ; 
}
	      if (mu__boolexpr166) {
		if ( ( TRUE  ) )
		  return;
		else
		  what_rule++;
	      }
	      else
		what_rule += 1;
	}
	else
	  what_rule += 1;
    r = what_rule - 18;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    mu_i.value((r % 1) + 3);
    r = r / 1;
    }
  }

  void Code(unsigned r)
  {
    static mu_1_ProcId mu_j;
    mu_j.value((r % 2) + 1);
    r = r / 2;
    static mu_1_MemoryId mu_i;
    mu_i.value((r % 1) + 3);
    r = r / 1;
/*** Variable declaration ***/
mu_1_ResPacket mu_outP("outP",0);

/*** Variable declaration ***/
mu_1_DataFlags mu_updates("updates",19);

/*** Variable declaration ***/
mu_1_SStatValues mu_status("status",23);

{
  mu_1_ReqPacket& mu_inP = mu_proc[mu_j].mu_exec.mu_reqPacket;
  mu_1_MemoryLine& mu_line = mu_memory[mu_i].mu_line[mu_proc[mu_j].mu_exec.mu_reqPacket.mu_offset];
mu_outP.undefine();
mu_outP.mu_cn = mu_false;
mu_outP.mu_co = mu_false;
mu_outP.mu_mCState = mu_line.mu_mState;
if ( (mu_line.mu_mState) != (mu_MS_HOME) )
{
mu_outP.mu_forwId = mu_line.mu_forwId;
}
switch ((int) mu_inP.mu_cmd) {
case mu_SC_MWRITE64:
case mu_SC_MREAD:
break;
default:
Error.Error("Error: memory behavior: transaction command not implemented");
break;
}
if ( !(mu_MOP_FRESH) )
{
Error.Error("Error: memory behavior: only MOP_FRESH implemented");
}
mu_updates = mu_MemoryTagUpdate( mu_line, mu_inP );
mu_status = mu_MemoryAccessBasic( mu_line, mu_inP, mu_outP );
switch ((int) mu_updates) {
case mu_NORM_DATA:
break;
case mu_NORM_NONE:
mu_outP.mu_cmd = mu_SC_RESP00;
break;
case mu_NORM_NULL:
mu_outP.mu_cmd = mu_SC_RESP00;
mu_outP.mu_cn = mu_true;
break;
case mu_NORM_SKIP:
mu_outP.mu_cn = mu_true;
break;
case mu_FULL_DATA:
mu_outP.mu_co = mu_true;
break;
case mu_FULL_NONE:
mu_outP.mu_cmd = mu_SC_RESP00;
mu_outP.mu_co = mu_true;
break;
case mu_FULL_NULL:
mu_outP.mu_cmd = mu_SC_RESP00;
mu_outP.mu_cn = mu_true;
mu_outP.mu_co = mu_true;
break;
default:
Error.Error("Error: memory behavior: MemoryTagUpdate return value not implemented");
break;
}
mu_SendResPacket ( mu_outP, (int)mu_inP.mu_sourceId );
mu_RemoveReqPacket ( mu_inP );
mu_UndefineUnusedValues (  );
}
  };

};
class NextStateGenerator
{
  RuleBase0 R0;
  RuleBase1 R1;
  RuleBase2 R2;
  RuleBase3 R3;
  RuleBase4 R4;
  RuleBase5 R5;
  RuleBase6 R6;
public:
void SetNextEnabledRule(unsigned & what_rule)
{
  category = CONDITION;
  if (what_rule<2)
    { R0.NextRule(what_rule);
      if (what_rule<2) return; }
  if (what_rule>=2 && what_rule<4)
    { R1.NextRule(what_rule);
      if (what_rule<4) return; }
  if (what_rule>=4 && what_rule<6)
    { R2.NextRule(what_rule);
      if (what_rule<6) return; }
  if (what_rule>=6 && what_rule<8)
    { R3.NextRule(what_rule);
      if (what_rule<8) return; }
  if (what_rule>=8 && what_rule<14)
    { R4.NextRule(what_rule);
      if (what_rule<14) return; }
  if (what_rule>=14 && what_rule<18)
    { R5.NextRule(what_rule);
      if (what_rule<18) return; }
  if (what_rule>=18 && what_rule<20)
    { R6.NextRule(what_rule);
      if (what_rule<20) return; }
}
bool Condition(unsigned r)
{
  category = CONDITION;
  if (r<=1) return R0.Condition(r-0);
  if (r>=2 && r<=3) return R1.Condition(r-2);
  if (r>=4 && r<=5) return R2.Condition(r-4);
  if (r>=6 && r<=7) return R3.Condition(r-6);
  if (r>=8 && r<=13) return R4.Condition(r-8);
  if (r>=14 && r<=17) return R5.Condition(r-14);
  if (r>=18 && r<=19) return R6.Condition(r-18);
Error.Notrace("Internal: NextStateGenerator -- checking condition for nonexisting rule.");
return 0;}
void Code(unsigned r)
{
  if (r<=1) { R0.Code(r-0); return; } 
  if (r>=2 && r<=3) { R1.Code(r-2); return; } 
  if (r>=4 && r<=5) { R2.Code(r-4); return; } 
  if (r>=6 && r<=7) { R3.Code(r-6); return; } 
  if (r>=8 && r<=13) { R4.Code(r-8); return; } 
  if (r>=14 && r<=17) { R5.Code(r-14); return; } 
  if (r>=18 && r<=19) { R6.Code(r-18); return; } 
}
int Priority(unsigned short r)
{
  if (r<=1) { return R0.Priority(); } 
  if (r>=2 && r<=3) { return R1.Priority(); } 
  if (r>=4 && r<=5) { return R2.Priority(); } 
  if (r>=6 && r<=7) { return R3.Priority(); } 
  if (r>=8 && r<=13) { return R4.Priority(); } 
  if (r>=14 && r<=17) { return R5.Priority(); } 
  if (r>=18 && r<=19) { return R6.Priority(); } 
return 0;}
char * Name(unsigned r)
{
  if (r<=1) return R0.Name(r-0);
  if (r>=2 && r<=3) return R1.Name(r-2);
  if (r>=4 && r<=5) return R2.Name(r-4);
  if (r>=6 && r<=7) return R3.Name(r-6);
  if (r>=8 && r<=13) return R4.Name(r-8);
  if (r>=14 && r<=17) return R5.Name(r-14);
  if (r>=18 && r<=19) return R6.Name(r-18);
  return NULL;
}
};
const unsigned numrules = 20;

/********************
  parameter
 ********************/
#define RULES_IN_WORLD 20


/********************
  Startstate records
 ********************/
/******************** StartStateBase0 ********************/
class StartStateBase0
{
public:
  char * Name(unsigned short r)
  {
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
    return tsprintf("Startstate 0, d:%s", mu_d.Name());
  }
  void Code(unsigned short r)
  {
    static mu_1_Data mu_d;
    mu_d.value((r % 1) + 6);
    r = r / 1;
mu_cacheUsage = mu_CU_GLOBAL;
{
for(int mu_i = 1; mu_i <= 2; mu_i++) {
mu_proc[mu_i].undefine();
mu_proc[mu_i].mu_exec.mu_state.mu_insType = mu_I_NONE;
{
for(int mu_j = 5; mu_j <= 5; mu_j++) {
mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState = mu_CS_INVALID;
};
};
};
};
{
for(int mu_i = 3; mu_i <= 3; mu_i++) {
mu_memory[mu_i].undefine();
{
for(int mu_j = 4; mu_j <= 4; mu_j++) {
mu_memory[mu_i].mu_line[mu_j].mu_mState = mu_MS_HOME;
mu_memory[mu_i].mu_line[mu_j].mu_data = mu_d;
};
};
};
};
  };

};
class StartStateGenerator
{
  StartStateBase0 S0;
public:
void Code(unsigned short r)
{
  if (r<=0) { S0.Code(r-0); return; }
}
char * Name(unsigned short r)
{
  if (r<=0) return S0.Name(r-0);
  return NULL;
}
};
const rulerec startstates[] = {
{ NULL, NULL, NULL, FALSE},
};
unsigned short StartStateManager::numstartstates = 1;

/********************
  Invariant records
 ********************/
int mu__invariant_168() // Invariant "sharing list head"
{
bool mu__quant169; 
mu__quant169 = TRUE;
{
for(int mu_i = 3; mu_i <= 3; mu_i++) {
bool mu__quant170; 
mu__quant170 = TRUE;
{
for(int mu_j = 4; mu_j <= 4; mu_j++) {
bool mu__boolexpr171;
bool mu__boolexpr172;
  if ((mu_memory[mu_i].mu_line[mu_j].mu_mState) == (mu_MS_FRESH)) mu__boolexpr172 = TRUE ;
  else {
  mu__boolexpr172 = ((mu_memory[mu_i].mu_line[mu_j].mu_mState) == (mu_MS_GONE)) ; 
}
  if (!(mu__boolexpr172)) mu__boolexpr171 = TRUE ;
  else {
bool mu__quant173; 
mu__quant173 = FALSE;
{
for(int mu_k = 5; mu_k <= 5; mu_k++) {
bool mu__boolexpr174;
bool mu__boolexpr175;
  if (!((mu_proc[mu_memory[mu_i].mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr175 = FALSE ;
  else {
  mu__boolexpr175 = ((mu_proc[mu_memory[mu_i].mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_memId) == (mu_i)) ; 
}
  if (!(mu__boolexpr175)) mu__boolexpr174 = FALSE ;
  else {
  mu__boolexpr174 = ((mu_proc[mu_memory[mu_i].mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_j)) ; 
}
if ( (mu__boolexpr174) )
  { mu__quant173 = TRUE; break; }
};
};
  mu__boolexpr171 = (mu__quant173) ; 
}
if ( !(mu__boolexpr171) )
  { mu__quant170 = FALSE; break; }
};
};
if ( !(mu__quant170) )
  { mu__quant169 = FALSE; break; }
};
};
return mu__quant169;
};

bool mu__condition_176() // Condition for Rule "sharing list head"
{
  return mu__invariant_168( );
}

/**** end rule declaration ****/

int mu__invariant_177() // Invariant "mid element neighbors"
{
bool mu__quant178; 
mu__quant178 = TRUE;
{
for(int mu_i = 1; mu_i <= 2; mu_i++) {
bool mu__quant179; 
mu__quant179 = TRUE;
{
for(int mu_j = 5; mu_j <= 5; mu_j++) {
bool mu__boolexpr180;
bool mu__boolexpr181;
  if ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_MID_VALID)) mu__boolexpr181 = TRUE ;
  else {
  mu__boolexpr181 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_MID_COPY)) ; 
}
  if (!(mu__boolexpr181)) mu__boolexpr180 = TRUE ;
  else {
bool mu__boolexpr182;
bool mu__quant183; 
mu__quant183 = FALSE;
{
for(int mu_k = 5; mu_k <= 5; mu_k++) {
bool mu__boolexpr184;
bool mu__boolexpr185;
bool mu__boolexpr186;
bool mu__boolexpr187;
  if (!((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr187 = FALSE ;
  else {
  mu__boolexpr187 = (!(mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_backId.isundefined())) ; 
}
  if (!(mu__boolexpr187)) mu__boolexpr186 = FALSE ;
  else {
  mu__boolexpr186 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_backId) == (mu_i)) ; 
}
  if (!(mu__boolexpr186)) mu__boolexpr185 = FALSE ;
  else {
  mu__boolexpr185 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_memId) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_memId)) ; 
}
  if (!(mu__boolexpr185)) mu__boolexpr184 = FALSE ;
  else {
  mu__boolexpr184 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_addrOffset)) ; 
}
if ( (mu__boolexpr184) )
  { mu__quant183 = TRUE; break; }
};
};
  if (!(mu__quant183)) mu__boolexpr182 = FALSE ;
  else {
bool mu__quant188; 
mu__quant188 = TRUE;
{
for(int mu_k = 5; mu_k <= 5; mu_k++) {
bool mu__boolexpr189;
bool mu__boolexpr190;
  if (mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_backId].mu_cache.mu_line[mu_k].mu_forwId.isundefined()) mu__boolexpr190 = TRUE ;
  else {
  mu__boolexpr190 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_backId].mu_cache.mu_line[mu_k].mu_forwId) != (mu_i)) ; 
}
  if (mu__boolexpr190) mu__boolexpr189 = TRUE ;
  else {
bool mu__boolexpr191;
bool mu__boolexpr192;
  if (!((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_backId].mu_cache.mu_line[mu_k].mu_forwId) == (mu_i))) mu__boolexpr192 = FALSE ;
  else {
  mu__boolexpr192 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_backId].mu_cache.mu_line[mu_k].mu_memId) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_memId)) ; 
}
  if (!(mu__boolexpr192)) mu__boolexpr191 = FALSE ;
  else {
  mu__boolexpr191 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_backId].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_addrOffset)) ; 
}
  mu__boolexpr189 = (mu__boolexpr191) ; 
}
if ( !(mu__boolexpr189) )
  { mu__quant188 = FALSE; break; }
};
};
  mu__boolexpr182 = (mu__quant188) ; 
}
  mu__boolexpr180 = (mu__boolexpr182) ; 
}
if ( !(mu__boolexpr180) )
  { mu__quant179 = FALSE; break; }
};
};
if ( !(mu__quant179) )
  { mu__quant178 = FALSE; break; }
};
};
return mu__quant178;
};

bool mu__condition_193() // Condition for Rule "mid element neighbors"
{
  return mu__invariant_177( );
}

/**** end rule declaration ****/

int mu__invariant_194() // Invariant "head element successor"
{
bool mu__quant195; 
mu__quant195 = TRUE;
{
for(int mu_i = 1; mu_i <= 2; mu_i++) {
bool mu__quant196; 
mu__quant196 = TRUE;
{
for(int mu_j = 5; mu_j <= 5; mu_j++) {
bool mu__boolexpr197;
bool mu__boolexpr198;
bool mu__boolexpr199;
  if ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_HEAD_DIRTY)) mu__boolexpr199 = TRUE ;
  else {
  mu__boolexpr199 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_HEAD_CLEAN)) ; 
}
  if (mu__boolexpr199) mu__boolexpr198 = TRUE ;
  else {
  mu__boolexpr198 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_HEAD_FRESH)) ; 
}
  if (!(mu__boolexpr198)) mu__boolexpr197 = TRUE ;
  else {
bool mu__quant200; 
mu__quant200 = FALSE;
{
for(int mu_k = 5; mu_k <= 5; mu_k++) {
bool mu__boolexpr201;
bool mu__boolexpr202;
bool mu__boolexpr203;
bool mu__boolexpr204;
  if (!((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_cState) != (mu_CS_INVALID))) mu__boolexpr204 = FALSE ;
  else {
  mu__boolexpr204 = (!(mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_backId.isundefined())) ; 
}
  if (!(mu__boolexpr204)) mu__boolexpr203 = FALSE ;
  else {
  mu__boolexpr203 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_backId) == (mu_i)) ; 
}
  if (!(mu__boolexpr203)) mu__boolexpr202 = FALSE ;
  else {
  mu__boolexpr202 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_memId) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_memId)) ; 
}
  if (!(mu__boolexpr202)) mu__boolexpr201 = FALSE ;
  else {
  mu__boolexpr201 = ((mu_proc[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_forwId].mu_cache.mu_line[mu_k].mu_addrOffset) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_addrOffset)) ; 
}
if ( (mu__boolexpr201) )
  { mu__quant200 = TRUE; break; }
};
};
  mu__boolexpr197 = (mu__quant200) ; 
}
if ( !(mu__boolexpr197) )
  { mu__quant196 = FALSE; break; }
};
};
if ( !(mu__quant196) )
  { mu__quant195 = FALSE; break; }
};
};
return mu__quant195;
};

bool mu__condition_205() // Condition for Rule "head element successor"
{
  return mu__invariant_194( );
}

/**** end rule declaration ****/

int mu__invariant_206() // Invariant "unmodified"
{
bool mu__quant207; 
mu__quant207 = TRUE;
{
for(int mu_i = 1; mu_i <= 2; mu_i++) {
bool mu__quant208; 
mu__quant208 = TRUE;
{
for(int mu_j = 5; mu_j <= 5; mu_j++) {
bool mu__boolexpr209;
bool mu__boolexpr210;
bool mu__boolexpr211;
bool mu__boolexpr212;
bool mu__boolexpr213;
bool mu__boolexpr214;
  if ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_ONLY_CLEAN)) mu__boolexpr214 = TRUE ;
  else {
  mu__boolexpr214 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_ONLY_FRESH)) ; 
}
  if (mu__boolexpr214) mu__boolexpr213 = TRUE ;
  else {
  mu__boolexpr213 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_HEAD_CLEAN)) ; 
}
  if (mu__boolexpr213) mu__boolexpr212 = TRUE ;
  else {
  mu__boolexpr212 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_HEAD_FRESH)) ; 
}
  if (mu__boolexpr212) mu__boolexpr211 = TRUE ;
  else {
  mu__boolexpr211 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_MID_COPY)) ; 
}
  if (mu__boolexpr211) mu__boolexpr210 = TRUE ;
  else {
  mu__boolexpr210 = ((mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_cState) == (mu_CS_TAIL_COPY)) ; 
}
  if (!(mu__boolexpr210)) mu__boolexpr209 = TRUE ;
  else {
  mu__boolexpr209 = ((mu_memory[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_memId].mu_line[mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_addrOffset].mu_data) == (mu_proc[mu_i].mu_cache.mu_line[mu_j].mu_data)) ; 
}
if ( !(mu__boolexpr209) )
  { mu__quant208 = FALSE; break; }
};
};
if ( !(mu__quant208) )
  { mu__quant207 = FALSE; break; }
};
};
return mu__quant207;
};

bool mu__condition_215() // Condition for Rule "unmodified"
{
  return mu__invariant_206( );
}

/**** end rule declaration ****/

const rulerec invariants[] = {
{"unmodified", &mu__condition_215, NULL, },
{"head element successor", &mu__condition_205, NULL, },
{"mid element neighbors", &mu__condition_193, NULL, },
{"sharing list head", &mu__condition_176, NULL, },
};
const unsigned short numinvariants = 4;

/********************
  Normal/Canonicalization for scalarset
 ********************/
/*
cacheUsage:NoScalarset
memory:ScalarsetVariable
proc:ScalarsetArrayOfScalarset
*/

/********************
Code for symmetry
 ********************/

/********************
 Permutation Set Class
 ********************/
class PermSet
{
public:
  // book keeping
  enum PresentationType {Simple, Explicit};
  PresentationType Presentation;

  void ResetToSimple();
  void ResetToExplicit();
  void SimpleToExplicit();
  void SimpleToOne();
  bool NextPermutation();

  void Print_in_size()
  { int ret=0; for (int i=0; i<count; i++) if (in[i]) ret++; cout << "in_size:" << ret << "\n"; }


  /********************
   Simple and efficient representation
   ********************/
  int class_mu_1_ProcId[2];
  int undefined_class_mu_1_ProcId;// has the highest class number

  void Print_class_mu_1_ProcId();
  bool OnlyOneRemain_mu_1_ProcId;
  bool MTO_class_mu_1_ProcId()
  {
    int i,j;
    if (OnlyOneRemain_mu_1_ProcId)
      return FALSE;
    for (i=0; i<2; i++)
      for (j=0; j<2; j++)
        if (i!=j && class_mu_1_ProcId[i]== class_mu_1_ProcId[j])
	    return TRUE;
    OnlyOneRemain_mu_1_ProcId = TRUE;
    return FALSE;
  }
  bool AlreadyOnlyOneRemain;
  bool MoreThanOneRemain();


  /********************
   Explicit representation
  ********************/
  unsigned long size;
  unsigned long count;
  // in will be of product of factorial sizes for fast canonicalize
  // in will be of size 1 for reduced local memory canonicalize
  bool * in;

  // auxiliary for explicit representation

  // in/perm/revperm will be of factorial size for fast canonicalize
  // they will be of size 1 for reduced local memory canonicalize
  // second range will be size of the scalarset
  int * in_mu_1_ProcId;
  typedef int arr_mu_1_ProcId[2];
  arr_mu_1_ProcId * perm_mu_1_ProcId;
  arr_mu_1_ProcId * revperm_mu_1_ProcId;

  int size_mu_1_ProcId[2];
  bool reversed_sorted_mu_1_ProcId(int start, int end);
  void reverse_reversed_mu_1_ProcId(int start, int end);

  // procedure for explicit representation
  bool ok0(mu_1_ProcId* perm, int size, mu_1_ProcId k);
  void GenPerm0(mu_1_ProcId* perm, int size, unsigned long& index);

  // General procedure
  PermSet();
  bool In(int i) const { return in[i]; };
  void Add(int i) { for (int j=0; j<i; j++) in[j] = FALSE;};
  void Remove(int i) { in[i] = FALSE; };
};
void PermSet::Print_class_mu_1_ProcId()
{
  cout << "class_mu_1_ProcId:\t";
  for (int i=0; i<2; i++)
    cout << class_mu_1_ProcId[i];
  cout << " " << undefined_class_mu_1_ProcId << "\n";
}
bool PermSet::MoreThanOneRemain()
{
  int i,j;
  if (AlreadyOnlyOneRemain)
    return FALSE;
  else {
    for (i=0; i<2; i++)
      for (j=0; j<2; j++)
        if (i!=j && class_mu_1_ProcId[i]== class_mu_1_ProcId[j])
	    return TRUE;
  }
  AlreadyOnlyOneRemain = TRUE;
  return FALSE;
}
PermSet::PermSet()
: Presentation(Simple)
{
  int i,j,k;
  if (  args->sym_alg.mode == argsym_alg::Exhaustive_Fast_Canonicalize
     || args->sym_alg.mode == argsym_alg::Heuristic_Fast_Canonicalize) {
    mu_1_ProcId Perm0[2];

  /********************
   declaration of class variables
  ********************/
  in = new bool[2];
 in_mu_1_ProcId = new int[2];
 perm_mu_1_ProcId = new arr_mu_1_ProcId[2];
 revperm_mu_1_ProcId = new arr_mu_1_ProcId[2];

    // Set perm and revperm
    count = 0;
    for (i=1; i<=2; i++)
      {
        Perm0[0].value(i);
        GenPerm0(Perm0, 1, count);
      }
    if (count!=2)
      Error.Error( "unable to initialize PermSet");
    for (i=0; i<2; i++)
      for (j=1; j<=2; j++)
        for (k=1; k<=2; k++)
          if (revperm_mu_1_ProcId[i][k-1]==j)   // k - base 
            perm_mu_1_ProcId[i][j-1]=k; // j - base 

    // setting up combination of permutations
    // for different scalarset
    int carry;
    int i_mu_1_ProcId = 0;
    size = 2;
    count = 2;
    for (i=0; i<2; i++)
      {
        carry = 1;
        in[i]= TRUE;
      in_mu_1_ProcId[i] = i_mu_1_ProcId;
      i_mu_1_ProcId += carry;
      if (i_mu_1_ProcId >= 2) { i_mu_1_ProcId = 0; carry = 1; } 
      else { carry = 0; } 
    }
  }
  else
  {

  /********************
   declaration of class variables
  ********************/
  in = new bool[1];
 in_mu_1_ProcId = new int[1];
 perm_mu_1_ProcId = new arr_mu_1_ProcId[1];
 revperm_mu_1_ProcId = new arr_mu_1_ProcId[1];
  in[0] = TRUE;
    in_mu_1_ProcId[0] = 0;
  }
}
void PermSet::ResetToSimple()
{
  int i;
  for (i=0; i<2; i++)
    class_mu_1_ProcId[i]=0;
  undefined_class_mu_1_ProcId=0;
  OnlyOneRemain_mu_1_ProcId = FALSE;

  AlreadyOnlyOneRemain = FALSE;
  Presentation = Simple;
}
void PermSet::ResetToExplicit()
{
  for (int i=0; i<2; i++) in[i] = TRUE;
  Presentation = Explicit;
}
void PermSet::SimpleToExplicit()
{
  int i,j,k;
  int start, class_size;
  int start_mu_1_ProcId[2];
  int size_mu_1_ProcId[2];
  bool should_be_in_mu_1_ProcId[2];

  // Setup range for mapping
  start = 0;
  for (j=0; j<=undefined_class_mu_1_ProcId; j++) // class number
    {
      class_size = 0;
      for (k=0; k<2; k++) // step through class_mu_1_pid[k]
	if (class_mu_1_ProcId[k]==j)
	  class_size++;
      for (k=0; k<2; k++) // step through class_mu_1_pid[k]
	if (class_mu_1_ProcId[k]==j)
	  {
	    size_mu_1_ProcId[k] = class_size;
	    start_mu_1_ProcId[k] = start;
	  }
      start+=class_size;
    }

  // To be In or not to be
  for (i=0; i<2; i++) // set up
    should_be_in_mu_1_ProcId[i] = TRUE;
  for (i=0; i<2; i++) // to be in or not to be
    for (k=0; k<2; k++) // step through class_mu_1_pid[k]
      if (! (perm_mu_1_ProcId[i][k]-1 >=start_mu_1_ProcId[k] 
	     && perm_mu_1_ProcId[i][k]-1 < start_mu_1_ProcId[k] + size_mu_1_ProcId[k]) )
  	    {
	      should_be_in_mu_1_ProcId[i] = FALSE;
	      break;
	    }

  // setup explicit representation 
  // Set perm and revperm
  for (i=0; i<2; i++)
    {
      in[i] = TRUE;
      if (in[i] && !should_be_in_mu_1_ProcId[in_mu_1_ProcId[i]]) in[i] = FALSE;
    }
  Presentation = Explicit;
  if (args->test_parameter1.value==0) Print_in_size();
}
void PermSet::SimpleToOne()
{
  int i,j,k;
  int class_size;
  int start;


  // Setup range for mapping
  start = 0;
  for (j=0; j<=undefined_class_mu_1_ProcId; j++) // class number
    {
      class_size = 0;
      for (k=0; k<2; k++) // step through class_mu_1_pid[k]
	if (class_mu_1_ProcId[k]==j)
	  class_size++;
      for (k=0; k<2; k++) // step through class_mu_1_pid[k]
	if (class_mu_1_ProcId[k]==j)
	  {
	    size_mu_1_ProcId[k] = class_size;
	  }
      start+=class_size;
    }
  start = 0;
  for (j=0; j<=undefined_class_mu_1_ProcId; j++) // class number
    {
      for (k=0; k<2; k++) // step through class_mu_1_pid[k]
	    if (class_mu_1_ProcId[k]==j)
	      revperm_mu_1_ProcId[0][start++] = k+1;
    }
  for (j=0; j<2; j++)
    for (k=0; k<2; k++)
      if (revperm_mu_1_ProcId[0][k]==j+1)
        perm_mu_1_ProcId[0][j]=k+1;
  Presentation = Explicit;
}
bool PermSet::ok0(mu_1_ProcId* Perm, int size, mu_1_ProcId k)
{
  for (int i=0; i<size; i++)
    if(Perm[i].value()==k)
      return FALSE;
  return TRUE;
}
void PermSet::GenPerm0(mu_1_ProcId* Perm,int size, unsigned long& count)
{
  int i;
  if (size!=2)
    {
      for (i=1; i<=2; i++)
        if(ok0(Perm,size,i))
          {
            Perm[size].value(i);
            GenPerm0(Perm, size+1, count);
          }
    }
  else
    {
      for (i=1; i<=2; i++)
        revperm_mu_1_ProcId[count][i-1]=Perm[i-1].value();// i - base
      count++;
    }
}
bool PermSet::reversed_sorted_mu_1_ProcId(int start, int end)
{
  int i,j;

  for (i=start; i<end; i++)
    if (revperm_mu_1_ProcId[0][i]<revperm_mu_1_ProcId[0][i+1])
      return FALSE;
  return TRUE;
}
void PermSet::reverse_reversed_mu_1_ProcId(int start, int end)
{
  int i,j;
  int temp;

  for (i=start, j=end; i<j; i++,j--) 
    {
      temp = revperm_mu_1_ProcId[0][j];
      revperm_mu_1_ProcId[0][j] = revperm_mu_1_ProcId[0][i];
      revperm_mu_1_ProcId[0][i] = temp;
    }
}
bool PermSet::NextPermutation()
{
  bool nexted = FALSE;
  int start, end; 
  int class_size;
  int temp;
  int j,k;

  // algorithm
  // for each class
  //   if forall in the same class reverse_sorted, 
  //     { sort again; goto next class }
  //   else
  //     {
  //       nexted = TRUE;
  //       for (j from l to r)
  // 	       if (for all j+ are reversed sorted)
  // 	         {
  // 	           swap j, j+1
  // 	           sort all j+ again
  // 	           break;
  // 	         }
  //     }
  for (start = 0; start < 2; )
    {
      end = start-1+size_mu_1_ProcId[revperm_mu_1_ProcId[0][start]-1];
      if (reversed_sorted_mu_1_ProcId(start,end))
	       {
	  reverse_reversed_mu_1_ProcId(start,end);
	  start = end+1;
	}
      else
	{
	  nexted = TRUE;
	  for (j = start; j<end; j++)
	    {
	      if (reversed_sorted_mu_1_ProcId(j+1,end))
		{
		  for (k = end; k>j; k--)
		    {
		      if (revperm_mu_1_ProcId[0][j]<revperm_mu_1_ProcId[0][k])
			{
			  // swap j, k
			  temp = revperm_mu_1_ProcId[0][j];
			  revperm_mu_1_ProcId[0][j] = revperm_mu_1_ProcId[0][k];
			  revperm_mu_1_ProcId[0][k] = temp;
			  break;
			}
		    }
		  reverse_reversed_mu_1_ProcId(j+1,end);
		  break;
		}
	    }
	  break;
	}
    }
if (!nexted) return FALSE;
  for (j=0; j<2; j++)
    for (k=0; k<2; k++)
      if (revperm_mu_1_ProcId[0][k]==j+1)   // k - base 
	perm_mu_1_ProcId[0][j]=k+1; // j - base 
  return TRUE;
}

/********************
 Symmetry Class
 ********************/
class SymmetryClass
{
  PermSet Perm;
  bool BestInitialized;
  state BestPermutedState;

  // utilities
  void SetBestResult(int i, state* temp);
  void ResetBestResult() {BestInitialized = FALSE;};

public:
  // initializer
  SymmetryClass() : Perm(), BestInitialized(FALSE) {};
  ~SymmetryClass() {};

  void Normalize(state* s);

  void Exhaustive_Fast_Canonicalize(state *s);
  void Heuristic_Fast_Canonicalize(state *s);
  void Heuristic_Small_Mem_Canonicalize(state *s);
  void Heuristic_Fast_Normalize(state *s);

  void MultisetSort(state* s);
};


/********************
 Symmetry Class Members
 ********************/
void SymmetryClass::MultisetSort(state* s)
{
        mu_cacheUsage.MultisetSort();
        mu_memory.MultisetSort();
        mu_proc.MultisetSort();
}
void SymmetryClass::Normalize(state* s)
{
  switch (args->sym_alg.mode) {
  case argsym_alg::Exhaustive_Fast_Canonicalize:
    Exhaustive_Fast_Canonicalize(s);
    break;
  case argsym_alg::Heuristic_Fast_Canonicalize:
    Heuristic_Fast_Canonicalize(s);
    break;
  case argsym_alg::Heuristic_Small_Mem_Canonicalize:
    Heuristic_Small_Mem_Canonicalize(s);
    break;
  case argsym_alg::Heuristic_Fast_Normalize:
    Heuristic_Fast_Normalize(s);
    break;
  default:
    Heuristic_Fast_Canonicalize(s);
  }
}

/********************
 Permute and Canonicalize function for different types
 ********************/
void mu_1_ProcId::Permute(PermSet& Perm, int i)
{
  if (Perm.Presentation != PermSet::Explicit)
    Error.Error("Internal Error: Wrong Sequence of Normalization");
  if (defined())
    value(Perm.perm_mu_1_ProcId[Perm.in_mu_1_ProcId[i]][value()-1]); // value - base
};
void mu_1_ProcId::SimpleCanonicalize(PermSet& Perm)
{
  int i, class_number;
  if (Perm.Presentation != PermSet::Simple)
    Error.Error("Internal Error: Wrong Sequence of Normalization");

  if (defined())
    if (Perm.class_mu_1_ProcId[value()-1]==Perm.undefined_class_mu_1_ProcId) // value - base
      {
        // it has not been mapped to any particular value
        for (i=0; i<2; i++)
          if (Perm.class_mu_1_ProcId[i] == Perm.undefined_class_mu_1_ProcId && i!=value()-1)
            Perm.class_mu_1_ProcId[i]++;
        value(1 + Perm.undefined_class_mu_1_ProcId++);
      }
    else 
      {
        value(Perm.class_mu_1_ProcId[value()-1]+1);
      }
}
void mu_1_ProcId::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_ProcId::SimpleLimit(PermSet& Perm)
{
  int i, class_number;
  if (Perm.Presentation != PermSet::Simple)
    Error.Error("Internal Error: Wrong Sequence of Normalization");

  if (defined())
    if (Perm.class_mu_1_ProcId[value()-1]==Perm.undefined_class_mu_1_ProcId) // value - base
      {
        // it has not been mapped to any particular value
        for (i=0; i<2; i++)
          if (Perm.class_mu_1_ProcId[i] == Perm.undefined_class_mu_1_ProcId && i!=value()-1)
            Perm.class_mu_1_ProcId[i]++;
        Perm.undefined_class_mu_1_ProcId++;
      }
}
void mu_1_ProcId::ArrayLimit(PermSet& Perm) {}
void mu_1_ProcId::Limit(PermSet& Perm) {}
void mu_1_ProcId::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset type.\n"); };
void mu_1_MemoryId::Permute(PermSet& Perm, int i) {}
void mu_1_MemoryId::SimpleCanonicalize(PermSet& Perm) {}
void mu_1_MemoryId::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_MemoryId::SimpleLimit(PermSet& Perm) {}
void mu_1_MemoryId::ArrayLimit(PermSet& Perm) {}
void mu_1_MemoryId::Limit(PermSet& Perm) {}
void mu_1_MemoryId::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset type.\n"); };
void mu_1_NodeId::Permute(PermSet& Perm, int i)
{
  if (Perm.Presentation != PermSet::Explicit)
    Error.Error("Internal Error: Wrong Sequence of Normalization");
  if (defined()) {
    if ( ( value() >= 1 ) && ( value() <= 2 ) )
      value(Perm.perm_mu_1_ProcId[Perm.in_mu_1_ProcId[i]][value()-1]+(0)); // value - base
  }
}
void mu_1_NodeId::SimpleCanonicalize(PermSet& Perm)
{
  int i, class_number;
  if (Perm.Presentation != PermSet::Simple)
    Error.Error("Internal Error: Wrong Sequence of Normalization");
  if (defined()) {
    if ( ( value() >= 1 ) && ( value() <= 2 ) )
      {
        if (Perm.class_mu_1_ProcId[value()-1]==Perm.undefined_class_mu_1_ProcId) // value - base
          {
            // it has not been mapped to any particular value
            for (i=0; i<2; i++)
              if (Perm.class_mu_1_ProcId[i] == Perm.undefined_class_mu_1_ProcId && i!=value()-1)
                Perm.class_mu_1_ProcId[i]++;
            value(1 + Perm.undefined_class_mu_1_ProcId++);
          }
        else 
          {
            value(Perm.class_mu_1_ProcId[value()-1]+1);
          }
      }
  }
}
void mu_1_NodeId::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_NodeId::SimpleLimit(PermSet& Perm)
{
  int i, class_number;
  if (Perm.Presentation != PermSet::Simple)
    Error.Error("Internal Error: Wrong Sequence of Normalization");
  if (defined()) {
    if ( ( value() >= 1 ) && ( value() <= 2 ) )
      if (Perm.class_mu_1_ProcId[value()-1]==Perm.undefined_class_mu_1_ProcId) // value - base
        {
          // it has not been mapped to any particular value
          for (i=0; i<2; i++)
            if (Perm.class_mu_1_ProcId[i] == Perm.undefined_class_mu_1_ProcId && i!=value()-1)
              Perm.class_mu_1_ProcId[i]++;
          Perm.undefined_class_mu_1_ProcId++;
        }
  }
}
void mu_1_NodeId::ArrayLimit(PermSet& Perm) {}
void mu_1_NodeId::Limit(PermSet& Perm) {}
void mu_1_NodeId::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for union type.\n"); };
void mu_1_MemoryLineId::Permute(PermSet& Perm, int i) {}
void mu_1_MemoryLineId::SimpleCanonicalize(PermSet& Perm) {}
void mu_1_MemoryLineId::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_MemoryLineId::SimpleLimit(PermSet& Perm) {}
void mu_1_MemoryLineId::ArrayLimit(PermSet& Perm) {}
void mu_1_MemoryLineId::Limit(PermSet& Perm) {}
void mu_1_MemoryLineId::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset type.\n"); };
void mu_1_CacheLineId::Permute(PermSet& Perm, int i) {}
void mu_1_CacheLineId::SimpleCanonicalize(PermSet& Perm) {}
void mu_1_CacheLineId::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_CacheLineId::SimpleLimit(PermSet& Perm) {}
void mu_1_CacheLineId::ArrayLimit(PermSet& Perm) {}
void mu_1_CacheLineId::Limit(PermSet& Perm) {}
void mu_1_CacheLineId::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset type.\n"); };
void mu_1_Data::Permute(PermSet& Perm, int i) {}
void mu_1_Data::SimpleCanonicalize(PermSet& Perm) {}
void mu_1_Data::Canonicalize(PermSet& Perm)
{
  Error.Error("Calling canonicalize() for Scalarset.");
}
void mu_1_Data::SimpleLimit(PermSet& Perm) {}
void mu_1_Data::ArrayLimit(PermSet& Perm) {}
void mu_1_Data::Limit(PermSet& Perm) {}
void mu_1_Data::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset type.\n"); };
void mu_1_AccessCommandsReq::Permute(PermSet& Perm, int i) {};
void mu_1_AccessCommandsReq::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_AccessCommandsReq::Canonicalize(PermSet& Perm) {};
void mu_1_AccessCommandsReq::SimpleLimit(PermSet& Perm) {};
void mu_1_AccessCommandsReq::ArrayLimit(PermSet& Perm) {};
void mu_1_AccessCommandsReq::Limit(PermSet& Perm) {};
void mu_1_AccessCommandsReq::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_AccessCommandsRes::Permute(PermSet& Perm, int i) {};
void mu_1_AccessCommandsRes::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_AccessCommandsRes::Canonicalize(PermSet& Perm) {};
void mu_1_AccessCommandsRes::SimpleLimit(PermSet& Perm) {};
void mu_1_AccessCommandsRes::ArrayLimit(PermSet& Perm) {};
void mu_1_AccessCommandsRes::Limit(PermSet& Perm) {};
void mu_1_AccessCommandsRes::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_MemoryCacheCommands::Permute(PermSet& Perm, int i) {};
void mu_1_MemoryCacheCommands::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_MemoryCacheCommands::Canonicalize(PermSet& Perm) {};
void mu_1_MemoryCacheCommands::SimpleLimit(PermSet& Perm) {};
void mu_1_MemoryCacheCommands::ArrayLimit(PermSet& Perm) {};
void mu_1_MemoryCacheCommands::Limit(PermSet& Perm) {};
void mu_1_MemoryCacheCommands::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_SStatValues::Permute(PermSet& Perm, int i) {};
void mu_1_SStatValues::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_SStatValues::Canonicalize(PermSet& Perm) {};
void mu_1_SStatValues::SimpleLimit(PermSet& Perm) {};
void mu_1_SStatValues::ArrayLimit(PermSet& Perm) {};
void mu_1_SStatValues::Limit(PermSet& Perm) {};
void mu_1_SStatValues::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_MemoryCacheStates::Permute(PermSet& Perm, int i) {};
void mu_1_MemoryCacheStates::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_MemoryCacheStates::Canonicalize(PermSet& Perm) {};
void mu_1_MemoryCacheStates::SimpleLimit(PermSet& Perm) {};
void mu_1_MemoryCacheStates::ArrayLimit(PermSet& Perm) {};
void mu_1_MemoryCacheStates::Limit(PermSet& Perm) {};
void mu_1_MemoryCacheStates::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_DataFlags::Permute(PermSet& Perm, int i) {};
void mu_1_DataFlags::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_DataFlags::Canonicalize(PermSet& Perm) {};
void mu_1_DataFlags::SimpleLimit(PermSet& Perm) {};
void mu_1_DataFlags::ArrayLimit(PermSet& Perm) {};
void mu_1_DataFlags::Limit(PermSet& Perm) {};
void mu_1_DataFlags::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_AccessTypes::Permute(PermSet& Perm, int i) {};
void mu_1_AccessTypes::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_AccessTypes::Canonicalize(PermSet& Perm) {};
void mu_1_AccessTypes::SimpleLimit(PermSet& Perm) {};
void mu_1_AccessTypes::ArrayLimit(PermSet& Perm) {};
void mu_1_AccessTypes::Limit(PermSet& Perm) {};
void mu_1_AccessTypes::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_FetchOptions::Permute(PermSet& Perm, int i) {};
void mu_1_FetchOptions::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_FetchOptions::Canonicalize(PermSet& Perm) {};
void mu_1_FetchOptions::SimpleLimit(PermSet& Perm) {};
void mu_1_FetchOptions::ArrayLimit(PermSet& Perm) {};
void mu_1_FetchOptions::Limit(PermSet& Perm) {};
void mu_1_FetchOptions::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_TransactStatus::Permute(PermSet& Perm, int i) {};
void mu_1_TransactStatus::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_TransactStatus::Canonicalize(PermSet& Perm) {};
void mu_1_TransactStatus::SimpleLimit(PermSet& Perm) {};
void mu_1_TransactStatus::ArrayLimit(PermSet& Perm) {};
void mu_1_TransactStatus::Limit(PermSet& Perm) {};
void mu_1_TransactStatus::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_FindFlags::Permute(PermSet& Perm, int i) {};
void mu_1_FindFlags::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_FindFlags::Canonicalize(PermSet& Perm) {};
void mu_1_FindFlags::SimpleLimit(PermSet& Perm) {};
void mu_1_FindFlags::ArrayLimit(PermSet& Perm) {};
void mu_1_FindFlags::Limit(PermSet& Perm) {};
void mu_1_FindFlags::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_BypassOptions::Permute(PermSet& Perm, int i) {};
void mu_1_BypassOptions::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_BypassOptions::Canonicalize(PermSet& Perm) {};
void mu_1_BypassOptions::SimpleLimit(PermSet& Perm) {};
void mu_1_BypassOptions::ArrayLimit(PermSet& Perm) {};
void mu_1_BypassOptions::Limit(PermSet& Perm) {};
void mu_1_BypassOptions::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_StableGroups::Permute(PermSet& Perm, int i) {};
void mu_1_StableGroups::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_StableGroups::Canonicalize(PermSet& Perm) {};
void mu_1_StableGroups::SimpleLimit(PermSet& Perm) {};
void mu_1_StableGroups::ArrayLimit(PermSet& Perm) {};
void mu_1_StableGroups::Limit(PermSet& Perm) {};
void mu_1_StableGroups::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_AttachStatus::Permute(PermSet& Perm, int i)
{
  mu_backId.Permute(Perm,i);
};
void mu_1_AttachStatus::SimpleCanonicalize(PermSet& Perm)
{
  mu_backId.SimpleCanonicalize(Perm);
};
void mu_1_AttachStatus::Canonicalize(PermSet& Perm)
{
};
void mu_1_AttachStatus::SimpleLimit(PermSet& Perm)
{
  mu_backId.SimpleLimit(Perm);
};
void mu_1_AttachStatus::ArrayLimit(PermSet& Perm){}
void mu_1_AttachStatus::Limit(PermSet& Perm)
{
};
void mu_1_AttachStatus::MultisetLimit(PermSet& Perm)
{
};
void mu_1_ReqPacket::Permute(PermSet& Perm, int i)
{
  mu_targetId.Permute(Perm,i);
  mu_sourceId.Permute(Perm,i);
  mu_newId.Permute(Perm,i);
  mu_memId.Permute(Perm,i);
};
void mu_1_ReqPacket::SimpleCanonicalize(PermSet& Perm)
{
  mu_targetId.SimpleCanonicalize(Perm);
  mu_sourceId.SimpleCanonicalize(Perm);
  mu_newId.SimpleCanonicalize(Perm);
  mu_memId.SimpleCanonicalize(Perm);
};
void mu_1_ReqPacket::Canonicalize(PermSet& Perm)
{
};
void mu_1_ReqPacket::SimpleLimit(PermSet& Perm)
{
  mu_targetId.SimpleLimit(Perm);
  mu_sourceId.SimpleLimit(Perm);
  mu_newId.SimpleLimit(Perm);
  mu_memId.SimpleLimit(Perm);
};
void mu_1_ReqPacket::ArrayLimit(PermSet& Perm){}
void mu_1_ReqPacket::Limit(PermSet& Perm)
{
};
void mu_1_ReqPacket::MultisetLimit(PermSet& Perm)
{
};
void mu_1_ResPacket::Permute(PermSet& Perm, int i)
{
  mu_forwId.Permute(Perm,i);
  mu_backId.Permute(Perm,i);
};
void mu_1_ResPacket::SimpleCanonicalize(PermSet& Perm)
{
  mu_forwId.SimpleCanonicalize(Perm);
  mu_backId.SimpleCanonicalize(Perm);
};
void mu_1_ResPacket::Canonicalize(PermSet& Perm)
{
};
void mu_1_ResPacket::SimpleLimit(PermSet& Perm)
{
  mu_forwId.SimpleLimit(Perm);
  mu_backId.SimpleLimit(Perm);
};
void mu_1_ResPacket::ArrayLimit(PermSet& Perm){}
void mu_1_ResPacket::Limit(PermSet& Perm)
{
};
void mu_1_ResPacket::MultisetLimit(PermSet& Perm)
{
};
void mu_1_MemoryLine::Permute(PermSet& Perm, int i)
{
  mu_forwId.Permute(Perm,i);
};
void mu_1_MemoryLine::SimpleCanonicalize(PermSet& Perm)
{
  mu_forwId.SimpleCanonicalize(Perm);
};
void mu_1_MemoryLine::Canonicalize(PermSet& Perm)
{
};
void mu_1_MemoryLine::SimpleLimit(PermSet& Perm)
{
  mu_forwId.SimpleLimit(Perm);
};
void mu_1_MemoryLine::ArrayLimit(PermSet& Perm){}
void mu_1_MemoryLine::Limit(PermSet& Perm)
{
};
void mu_1_MemoryLine::MultisetLimit(PermSet& Perm)
{
};
void mu_1__type_0::Permute(PermSet& Perm, int i)
{
  static mu_1__type_0 temp("Permute_mu_1__type_0",-1);
  int j;
  for (j=0; j<1; j++)
    array[j].Permute(Perm, i);
};
void mu_1__type_0::SimpleCanonicalize(PermSet& Perm)
{
  for (int j=0; j<1; j++)
    array[j].SimpleCanonicalize(Perm);
}
void mu_1__type_0::Canonicalize(PermSet& Perm){};
void mu_1__type_0::SimpleLimit(PermSet& Perm)
{
  for (int j=0; j<1; j++) {
    array[j].SimpleLimit(Perm);
  }
}
void mu_1__type_0::ArrayLimit(PermSet& Perm) {}
void mu_1__type_0::Limit(PermSet& Perm){}
void mu_1__type_0::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset array.\n"); };
void mu_1_Memory::Permute(PermSet& Perm, int i)
{
  mu_line.Permute(Perm,i);
};
void mu_1_Memory::SimpleCanonicalize(PermSet& Perm)
{
  mu_line.SimpleCanonicalize(Perm);
};
void mu_1_Memory::Canonicalize(PermSet& Perm)
{
};
void mu_1_Memory::SimpleLimit(PermSet& Perm)
{
  mu_line.SimpleLimit(Perm);
};
void mu_1_Memory::ArrayLimit(PermSet& Perm){}
void mu_1_Memory::Limit(PermSet& Perm)
{
};
void mu_1_Memory::MultisetLimit(PermSet& Perm)
{
};
void mu_1_CacheLine::Permute(PermSet& Perm, int i)
{
  mu_forwId.Permute(Perm,i);
  mu_backId.Permute(Perm,i);
  mu_memId.Permute(Perm,i);
};
void mu_1_CacheLine::SimpleCanonicalize(PermSet& Perm)
{
  mu_forwId.SimpleCanonicalize(Perm);
  mu_backId.SimpleCanonicalize(Perm);
  mu_memId.SimpleCanonicalize(Perm);
};
void mu_1_CacheLine::Canonicalize(PermSet& Perm)
{
};
void mu_1_CacheLine::SimpleLimit(PermSet& Perm)
{
  mu_forwId.SimpleLimit(Perm);
  mu_backId.SimpleLimit(Perm);
  mu_memId.SimpleLimit(Perm);
};
void mu_1_CacheLine::ArrayLimit(PermSet& Perm){}
void mu_1_CacheLine::Limit(PermSet& Perm)
{
};
void mu_1_CacheLine::MultisetLimit(PermSet& Perm)
{
};
void mu_1__type_1::Permute(PermSet& Perm, int i)
{
  static mu_1__type_1 temp("Permute_mu_1__type_1",-1);
  int j;
  for (j=0; j<1; j++)
    array[j].Permute(Perm, i);
};
void mu_1__type_1::SimpleCanonicalize(PermSet& Perm)
{
  for (int j=0; j<1; j++)
    array[j].SimpleCanonicalize(Perm);
}
void mu_1__type_1::Canonicalize(PermSet& Perm){};
void mu_1__type_1::SimpleLimit(PermSet& Perm)
{
  for (int j=0; j<1; j++) {
    array[j].SimpleLimit(Perm);
  }
}
void mu_1__type_1::ArrayLimit(PermSet& Perm) {}
void mu_1__type_1::Limit(PermSet& Perm){}
void mu_1__type_1::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset array.\n"); };
void mu_1_Cache::Permute(PermSet& Perm, int i)
{
  mu_line.Permute(Perm,i);
};
void mu_1_Cache::SimpleCanonicalize(PermSet& Perm)
{
  mu_line.SimpleCanonicalize(Perm);
};
void mu_1_Cache::Canonicalize(PermSet& Perm)
{
};
void mu_1_Cache::SimpleLimit(PermSet& Perm)
{
  mu_line.SimpleLimit(Perm);
};
void mu_1_Cache::ArrayLimit(PermSet& Perm){}
void mu_1_Cache::Limit(PermSet& Perm)
{
};
void mu_1_Cache::MultisetLimit(PermSet& Perm)
{
};
void mu_1_InstructionType::Permute(PermSet& Perm, int i) {};
void mu_1_InstructionType::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_InstructionType::Canonicalize(PermSet& Perm) {};
void mu_1_InstructionType::SimpleLimit(PermSet& Perm) {};
void mu_1_InstructionType::ArrayLimit(PermSet& Perm) {};
void mu_1_InstructionType::Limit(PermSet& Perm) {};
void mu_1_InstructionType::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_InstructionPhase::Permute(PermSet& Perm, int i) {};
void mu_1_InstructionPhase::SimpleCanonicalize(PermSet& Perm) {};
void mu_1_InstructionPhase::Canonicalize(PermSet& Perm) {};
void mu_1_InstructionPhase::SimpleLimit(PermSet& Perm) {};
void mu_1_InstructionPhase::ArrayLimit(PermSet& Perm) {};
void mu_1_InstructionPhase::Limit(PermSet& Perm) {};
void mu_1_InstructionPhase::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for enum type.\n"); };
void mu_1_LB::Permute(PermSet& Perm, int i)
{
};
void mu_1_LB::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Record with no scalarset variable\n"); };
void mu_1_LB::Canonicalize(PermSet& Perm)
{
};
void mu_1_LB::SimpleLimit(PermSet& Perm){}
void mu_1_LB::ArrayLimit(PermSet& Perm){}
void mu_1_LB::Limit(PermSet& Perm)
{
};
void mu_1_LB::MultisetLimit(PermSet& Perm)
{
};
void mu_1_LC::Permute(PermSet& Perm, int i)
{
};
void mu_1_LC::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Record with no scalarset variable\n"); };
void mu_1_LC::Canonicalize(PermSet& Perm)
{
};
void mu_1_LC::SimpleLimit(PermSet& Perm){}
void mu_1_LC::ArrayLimit(PermSet& Perm){}
void mu_1_LC::Limit(PermSet& Perm)
{
};
void mu_1_LC::MultisetLimit(PermSet& Perm)
{
};
void mu_1_SubState::Permute(PermSet& Perm, int i)
{
};
void mu_1_SubState::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Record with no scalarset variable\n"); };
void mu_1_SubState::Canonicalize(PermSet& Perm)
{
};
void mu_1_SubState::SimpleLimit(PermSet& Perm){}
void mu_1_SubState::ArrayLimit(PermSet& Perm){}
void mu_1_SubState::Limit(PermSet& Perm)
{
};
void mu_1_SubState::MultisetLimit(PermSet& Perm)
{
};
void mu_1_L0::Permute(PermSet& Perm, int i)
{
};
void mu_1_L0::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Record with no scalarset variable\n"); };
void mu_1_L0::Canonicalize(PermSet& Perm)
{
};
void mu_1_L0::SimpleLimit(PermSet& Perm){}
void mu_1_L0::ArrayLimit(PermSet& Perm){}
void mu_1_L0::Limit(PermSet& Perm)
{
};
void mu_1_L0::MultisetLimit(PermSet& Perm)
{
};
void mu_1_L1::Permute(PermSet& Perm, int i)
{
};
void mu_1_L1::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Record with no scalarset variable\n"); };
void mu_1_L1::Canonicalize(PermSet& Perm)
{
};
void mu_1_L1::SimpleLimit(PermSet& Perm){}
void mu_1_L1::ArrayLimit(PermSet& Perm){}
void mu_1_L1::Limit(PermSet& Perm)
{
};
void mu_1_L1::MultisetLimit(PermSet& Perm)
{
};
void mu_1_L2::Permute(PermSet& Perm, int i)
{
  mu_nextId.Permute(Perm,i);
};
void mu_1_L2::SimpleCanonicalize(PermSet& Perm)
{
  mu_nextId.SimpleCanonicalize(Perm);
};
void mu_1_L2::Canonicalize(PermSet& Perm)
{
};
void mu_1_L2::SimpleLimit(PermSet& Perm)
{
  mu_nextId.SimpleLimit(Perm);
};
void mu_1_L2::ArrayLimit(PermSet& Perm){}
void mu_1_L2::Limit(PermSet& Perm)
{
};
void mu_1_L2::MultisetLimit(PermSet& Perm)
{
};
void mu_1_ToState::Permute(PermSet& Perm, int i)
{
  mu_l2.Permute(Perm,i);
};
void mu_1_ToState::SimpleCanonicalize(PermSet& Perm)
{
  mu_l2.SimpleCanonicalize(Perm);
};
void mu_1_ToState::Canonicalize(PermSet& Perm)
{
};
void mu_1_ToState::SimpleLimit(PermSet& Perm)
{
  mu_l2.SimpleLimit(Perm);
};
void mu_1_ToState::ArrayLimit(PermSet& Perm){}
void mu_1_ToState::Limit(PermSet& Perm)
{
};
void mu_1_ToState::MultisetLimit(PermSet& Perm)
{
};
void mu_1_ExecState::Permute(PermSet& Perm, int i)
{
  mu_toState.Permute(Perm,i);
};
void mu_1_ExecState::SimpleCanonicalize(PermSet& Perm)
{
  mu_toState.SimpleCanonicalize(Perm);
};
void mu_1_ExecState::Canonicalize(PermSet& Perm)
{
};
void mu_1_ExecState::SimpleLimit(PermSet& Perm)
{
  mu_toState.SimpleLimit(Perm);
};
void mu_1_ExecState::ArrayLimit(PermSet& Perm){}
void mu_1_ExecState::Limit(PermSet& Perm)
{
};
void mu_1_ExecState::MultisetLimit(PermSet& Perm)
{
};
void mu_1_ExecUnit::Permute(PermSet& Perm, int i)
{
  mu_state.Permute(Perm,i);
  mu_reqPacket.Permute(Perm,i);
  mu_resPacket.Permute(Perm,i);
};
void mu_1_ExecUnit::SimpleCanonicalize(PermSet& Perm)
{
  mu_state.SimpleCanonicalize(Perm);
  mu_reqPacket.SimpleCanonicalize(Perm);
  mu_resPacket.SimpleCanonicalize(Perm);
};
void mu_1_ExecUnit::Canonicalize(PermSet& Perm)
{
};
void mu_1_ExecUnit::SimpleLimit(PermSet& Perm)
{
  mu_state.SimpleLimit(Perm);
  mu_reqPacket.SimpleLimit(Perm);
  mu_resPacket.SimpleLimit(Perm);
};
void mu_1_ExecUnit::ArrayLimit(PermSet& Perm){}
void mu_1_ExecUnit::Limit(PermSet& Perm)
{
};
void mu_1_ExecUnit::MultisetLimit(PermSet& Perm)
{
};
void mu_1_Proc::Permute(PermSet& Perm, int i)
{
  mu_exec.Permute(Perm,i);
  mu_cache.Permute(Perm,i);
};
void mu_1_Proc::SimpleCanonicalize(PermSet& Perm)
{
  mu_exec.SimpleCanonicalize(Perm);
  mu_cache.SimpleCanonicalize(Perm);
};
void mu_1_Proc::Canonicalize(PermSet& Perm)
{
};
void mu_1_Proc::SimpleLimit(PermSet& Perm)
{
  mu_exec.SimpleLimit(Perm);
  mu_cache.SimpleLimit(Perm);
};
void mu_1_Proc::ArrayLimit(PermSet& Perm){}
void mu_1_Proc::Limit(PermSet& Perm)
{
};
void mu_1_Proc::MultisetLimit(PermSet& Perm)
{
};
void mu_1__type_2::Permute(PermSet& Perm, int i)
{
  static mu_1__type_2 temp("Permute_mu_1__type_2",-1);
  int j;
  for (j=0; j<2; j++)
    array[j].Permute(Perm, i);
  temp = *this;
  for (j=1; j<=2; j++)
    (*this)[j] = temp[Perm.revperm_mu_1_ProcId[Perm.in_mu_1_ProcId[i]][j-1]];};
void mu_1__type_2::SimpleCanonicalize(PermSet& Perm)
{ Error.Error("Internal: Simple Canonicalization of Scalarset Array\n"); };
void mu_1__type_2::Canonicalize(PermSet& Perm){};
void mu_1__type_2::SimpleLimit(PermSet& Perm){}
void mu_1__type_2::ArrayLimit(PermSet& Perm)
{
  // indexes
  int i,j,k,z;
  // sorting
  int count_mu_1_ProcId;
  int compare;
  static mu_1_Proc value[2];
  // limit
  bool exists;
  bool split;
  bool goodset_mu_1_ProcId[2];
  bool pos_mu_1_ProcId[2][2];
  // sorting mu_1_ProcId
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId())
    {
      for (i=0; i<2; i++)
        for (j=0; j<2; j++)
          pos_mu_1_ProcId[i][j]=FALSE;
      count_mu_1_ProcId = 0;
      for (i=0; i<2; i++)
        {
          for (j=0; j<count_mu_1_ProcId; j++)
            {
              compare = CompareWeight(value[j],(*this)[i+1]);
              if (compare==0)
                {
                  pos_mu_1_ProcId[j][i]= TRUE;
                  break;
                }
              else if (compare>0)
                {
                  for (k=count_mu_1_ProcId; k>j; k--)
                    {
                      value[k] = value[k-1];
                      for (z=0; z<2; z++)
                        pos_mu_1_ProcId[k][z] = pos_mu_1_ProcId[k-1][z];
                    }
                  value[j] = (*this)[i+1];
                  for (z=0; z<2; z++)
                    pos_mu_1_ProcId[j][z] = FALSE;
                  pos_mu_1_ProcId[j][i] = TRUE;
                  count_mu_1_ProcId++;
                  break;
                }
            }
          if (j==count_mu_1_ProcId)
            {
              value[j] = (*this)[i+1];
              for (z=0; z<2; z++)
                pos_mu_1_ProcId[j][z] = FALSE;
              pos_mu_1_ProcId[j][i] = TRUE;
              count_mu_1_ProcId++;
            }
        }
    }
  // if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId>1)
    {
      // limit
      for (j=0; j<2; j++) // class priority
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] && Perm.class_mu_1_ProcId[k] == j)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                    pos_mu_1_ProcId[i][k] = FALSE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( Perm.class_mu_1_ProcId[k] == j && !goodset_mu_1_ProcId[k] ) 
                      split= TRUE;
                  if (split)
                    {
                      for (k=0; k<2; k++)
                        if (Perm.class_mu_1_ProcId[k]>j
                            || ( Perm.class_mu_1_ProcId[k] == j && !goodset_mu_1_ProcId[k] ) )
                          Perm.class_mu_1_ProcId[k]++;
                      Perm.undefined_class_mu_1_ProcId++;
                    }
                }
            }
        }
    }
}
void mu_1__type_2::Limit(PermSet& Perm)
{
  // indexes
  int i,j,k,z;
  // while guard
  bool while_guard, while_guard_temp;
  // sorting
  static mu_1_Proc value[2];
  // limit
  bool exists;
  bool split;
  int i0;
  int count_mu_1_ProcId, oldcount_mu_1_ProcId;
  bool pos_mu_1_ProcId[2][2];
  bool goodset_mu_1_ProcId[2];
  // count_ corresponds to the number of equivalence class within the
  // scalarset value.  If count_ == size of the scalarset, then a unique
  // permutation has been found.

  // pos_ is a relation on a equivalence class number and a scalarset value.

  // initializing pos array
  for (i=0; i<2; i++)
    for (j=0; j<2; j++)
      pos_mu_1_ProcId[i][j]=FALSE;
  count_mu_1_ProcId = 0;
  while (1)
    {
      exists = FALSE;
      for (i=0; i<2; i++)
       if (Perm.class_mu_1_ProcId[i] == count_mu_1_ProcId)
         {
           pos_mu_1_ProcId[count_mu_1_ProcId][i]=TRUE;
           exists = TRUE;
         }
      if (exists) count_mu_1_ProcId++;
      else break;
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId.isundefined()
            ||(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId.isundefined()
                    && (*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_reqPacket.mu_targetId.isundefined()
            ||(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId.isundefined()
                    && (*this)[k+1].mu_exec.mu_reqPacket.mu_targetId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId.isundefined()
            ||(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId.isundefined()
                    && (*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_reqPacket.mu_newId.isundefined()
            ||(*this)[k+1].mu_exec.mu_reqPacket.mu_newId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_reqPacket.mu_newId.isundefined()
                    && (*this)[k+1].mu_exec.mu_reqPacket.mu_newId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_reqPacket.mu_memId.isundefined()
            ||(*this)[k+1].mu_exec.mu_reqPacket.mu_memId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_reqPacket.mu_memId.isundefined()
                    && (*this)[k+1].mu_exec.mu_reqPacket.mu_memId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_resPacket.mu_forwId.isundefined()
            ||(*this)[k+1].mu_exec.mu_resPacket.mu_forwId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_resPacket.mu_forwId.isundefined()
                    && (*this)[k+1].mu_exec.mu_resPacket.mu_forwId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_exec.mu_resPacket.mu_backId.isundefined()
            ||(*this)[k+1].mu_exec.mu_resPacket.mu_backId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_exec.mu_resPacket.mu_backId.isundefined()
                    && (*this)[k+1].mu_exec.mu_resPacket.mu_backId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId.isundefined()
            ||(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId.isundefined()
                    && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId.isundefined()
            ||(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId.isundefined()
                    && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- check selfloop
  // only if there is more than 1 permutation in class
  if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
    {
      exists = FALSE;
      split = FALSE;
      // if there exists both self loop and non-self loop
      for (k=0; k<2; k++) // step through class
        if ((*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId.isundefined()
            ||(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId!=k+1)
          exists = TRUE;
        else
          split = TRUE;
      if (exists && split)
        {
          for (i=0; i<count_mu_1_ProcId; i++) // for value priority
            {
              exists = FALSE;
              for (k=0; k<2; k++) // step through class
                goodset_mu_1_ProcId[k] = FALSE;
              for (k=0; k<2; k++) // step through class
                if (pos_mu_1_ProcId[i][k] 
                    && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId.isundefined()
                    && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId==k+1)
                  {
                    exists = TRUE;
                    goodset_mu_1_ProcId[k] = TRUE;
                  }
              if (exists)
                {
                  split=FALSE;
                  for (k=0; k<2; k++)
                    if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                          split= TRUE;
                  if (split)
                    {
                      for (j=count_mu_1_ProcId; j>i; j--)
                        for (k=0; k<2; k++)
                          pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                      for (k=0; k<2; k++)
                        {
                          if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i][k] = FALSE;
                          if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                            pos_mu_1_ProcId[i+1][k] = FALSE;
                        }
                      count_mu_1_ProcId++; i++;
                    }
                }
            }
        }
    }

  // refinement -- checking priority in general
  while_guard = FALSE;
  while_guard = while_guard || (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2);
  while ( while_guard )
    {
      oldcount_mu_1_ProcId = count_mu_1_ProcId;

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          // if there exists non-self/undefine loop
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId.isundefined()
                &&(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId!=k+1)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId.isundefined()
                            && (*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId!=k+1
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_state.mu_toState.mu_l2.mu_nextId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId.isundefined()
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId!=k+1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId>=1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId.isundefined()
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_targetId!=k+1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_targetId>=1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_targetId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_reqPacket.mu_targetId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId.isundefined()
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId!=k+1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId>=1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId.isundefined()
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId!=k+1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId>=1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_reqPacket.mu_sourceId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_reqPacket.mu_newId.isundefined()
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_newId!=k+1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_newId>=1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_newId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_reqPacket.mu_newId.isundefined()
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_newId!=k+1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_newId>=1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_newId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_reqPacket.mu_newId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_reqPacket.mu_memId.isundefined()
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_memId!=k+1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_memId>=1
                &&(*this)[k+1].mu_exec.mu_reqPacket.mu_memId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_reqPacket.mu_memId.isundefined()
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_memId!=k+1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_memId>=1
                            && (*this)[k+1].mu_exec.mu_reqPacket.mu_memId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_reqPacket.mu_memId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_resPacket.mu_forwId.isundefined()
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_forwId!=k+1
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_forwId>=1
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_forwId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_resPacket.mu_forwId.isundefined()
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_forwId!=k+1
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_forwId>=1
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_forwId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_resPacket.mu_forwId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_exec.mu_resPacket.mu_backId.isundefined()
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_backId!=k+1
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_backId>=1
                &&(*this)[k+1].mu_exec.mu_resPacket.mu_backId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_exec.mu_resPacket.mu_backId.isundefined()
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_backId!=k+1
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_backId>=1
                            && (*this)[k+1].mu_exec.mu_resPacket.mu_backId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_exec.mu_resPacket.mu_backId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId.isundefined()
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId!=k+1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId>=1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId.isundefined()
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId!=k+1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId>=1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_forwId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId.isundefined()
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId!=k+1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId>=1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId.isundefined()
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId!=k+1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId>=1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_backId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }

      // refinement -- graph structure for a single scalarset
      //               as in array S1 of S1
      // only if there is more than 1 permutation in class
      if (Perm.MTO_class_mu_1_ProcId() && count_mu_1_ProcId<2)
        {
          exists = FALSE;
          split = FALSE;
          for (k=0; k<2; k++) // step through class
            if (!(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId.isundefined()
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId!=k+1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId>=1
                &&(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId<=2)
              exists = TRUE;
          if (exists)
            {
              for (i=0; i<count_mu_1_ProcId; i++) // for value priority
                {
                  for (j=0; j<count_mu_1_ProcId; j++) // for value priority
                    {
                      exists = FALSE;
                      for (k=0; k<2; k++) // step through class
                        goodset_mu_1_ProcId[k] = FALSE;
                      for (k=0; k<2; k++) // step through class
                        if (pos_mu_1_ProcId[i][k] 
                            && !(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId.isundefined()
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId!=k+1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId>=1
                            && (*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId<=2
                            && pos_mu_1_ProcId[j][(*this)[k+1].mu_cache.mu_line[mu_CacheLineId_1].mu_memId-1])
                          {
                            exists = TRUE;
                            goodset_mu_1_ProcId[k] = TRUE;
                          }
                      if (exists)
                        {
                          split=FALSE;
                          for (k=0; k<2; k++)
                            if ( pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k] ) 
                              split= TRUE;
                          if (split)
                            {
                              for (j=count_mu_1_ProcId; j>i; j--)
                                for (k=0; k<2; k++)
                                  pos_mu_1_ProcId[j][k] = pos_mu_1_ProcId[j-1][k];
                              for (k=0; k<2; k++)
                                {
                                  if (pos_mu_1_ProcId[i][k] && !goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i][k] = FALSE;
                                  if (pos_mu_1_ProcId[i+1][k] && goodset_mu_1_ProcId[k])
                                    pos_mu_1_ProcId[i+1][k] = FALSE;                  
                                }
                              count_mu_1_ProcId++;
                            }
                        }
                    }
                }
            }
        }
      while_guard = FALSE;
      while_guard = while_guard || (oldcount_mu_1_ProcId!=count_mu_1_ProcId);
      while_guard_temp = while_guard;
      while_guard = FALSE;
      while_guard = while_guard || count_mu_1_ProcId<2;
      while_guard = while_guard && while_guard_temp;
    } // end while
  // enter the result into class
  if (Perm.MTO_class_mu_1_ProcId())
    {
      for (i=0; i<2; i++)
        for (j=0; j<2; j++)
          if (pos_mu_1_ProcId[i][j])
            Perm.class_mu_1_ProcId[j] = i;
      Perm.undefined_class_mu_1_ProcId=0;
      for (j=0; j<2; j++)
        if (Perm.class_mu_1_ProcId[j]>Perm.undefined_class_mu_1_ProcId)
          Perm.undefined_class_mu_1_ProcId=Perm.class_mu_1_ProcId[j];
    }
}
void mu_1__type_2::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset array.\n"); };
void mu_1__type_3::Permute(PermSet& Perm, int i)
{
  static mu_1__type_3 temp("Permute_mu_1__type_3",-1);
  int j;
  for (j=0; j<1; j++)
    array[j].Permute(Perm, i);
};
void mu_1__type_3::SimpleCanonicalize(PermSet& Perm)
{
  for (int j=0; j<1; j++)
    array[j].SimpleCanonicalize(Perm);
}
void mu_1__type_3::Canonicalize(PermSet& Perm){};
void mu_1__type_3::SimpleLimit(PermSet& Perm)
{
  for (int j=0; j<1; j++) {
    array[j].SimpleLimit(Perm);
  }
}
void mu_1__type_3::ArrayLimit(PermSet& Perm) {}
void mu_1__type_3::Limit(PermSet& Perm){}
void mu_1__type_3::MultisetLimit(PermSet& Perm)
{ Error.Error("Internal: calling MultisetLimit for scalarset array.\n"); };

/********************
 Auxiliary function for error trace printing
 ********************/
bool match(state* ns, StatePtr p)
{
  int i;
  static PermSet Perm;
  static state temp;
  StateCopy(&temp, ns);
  if (args->symmetry_reduction.value)
    {
      if (  args->sym_alg.mode == argsym_alg::Exhaustive_Fast_Canonicalize
         || args->sym_alg.mode == argsym_alg::Heuristic_Fast_Canonicalize) {
        Perm.ResetToExplicit();
        for (i=0; i<Perm.count; i++)
          if (Perm.In(i))
            {
              if (ns != workingstate)
                  StateCopy(workingstate, ns);
              
              mu_cacheUsage.Permute(Perm,i);
              if (args->multiset_reduction.value)
                mu_cacheUsage.MultisetSort();
              mu_memory.Permute(Perm,i);
              if (args->multiset_reduction.value)
                mu_memory.MultisetSort();
              mu_proc.Permute(Perm,i);
              if (args->multiset_reduction.value)
                mu_proc.MultisetSort();
            if (p.compare(workingstate)) {
              StateCopy(workingstate,&temp); return TRUE; }
          }
        StateCopy(workingstate,&temp);
        return FALSE;
      }
      else {
        Perm.ResetToSimple();
        Perm.SimpleToOne();
        if (ns != workingstate)
          StateCopy(workingstate, ns);

          mu_cacheUsage.Permute(Perm,0);
          if (args->multiset_reduction.value)
            mu_cacheUsage.MultisetSort();
          mu_memory.Permute(Perm,0);
          if (args->multiset_reduction.value)
            mu_memory.MultisetSort();
          mu_proc.Permute(Perm,0);
          if (args->multiset_reduction.value)
            mu_proc.MultisetSort();
        if (p.compare(workingstate)) {
          StateCopy(workingstate,&temp); return TRUE; }

        while (Perm.NextPermutation())
          {
            if (ns != workingstate)
              StateCopy(workingstate, ns);
              
              mu_cacheUsage.Permute(Perm,0);
              if (args->multiset_reduction.value)
                mu_cacheUsage.MultisetSort();
              mu_memory.Permute(Perm,0);
              if (args->multiset_reduction.value)
                mu_memory.MultisetSort();
              mu_proc.Permute(Perm,0);
              if (args->multiset_reduction.value)
                mu_proc.MultisetSort();
            if (p.compare(workingstate)) {
              StateCopy(workingstate,&temp); return TRUE; }
          }
        StateCopy(workingstate,&temp);
        return FALSE;
      }
    }
  if (!args->symmetry_reduction.value
      && args->multiset_reduction.value)
    {
      if (ns != workingstate)
          StateCopy(workingstate, ns);
      mu_cacheUsage.MultisetSort();
      mu_memory.MultisetSort();
      mu_proc.MultisetSort();
      if (p.compare(workingstate)) {
        StateCopy(workingstate,&temp); return TRUE; }
      StateCopy(workingstate,&temp);
      return FALSE;
    }
  return (p.compare(ns));
}

/********************
 Canonicalization by fast exhaustive generation of
 all permutations
 ********************/
void SymmetryClass::Exhaustive_Fast_Canonicalize(state* s)
{
  int i;
  static state temp;
  Perm.ResetToExplicit();

  StateCopy(&temp, workingstate);
  ResetBestResult();
  for (i=0; i<Perm.count; i++)
    if (Perm.In(i))
      {
        StateCopy(workingstate, &temp);
        mu_cacheUsage.Permute(Perm,i);
        if (args->multiset_reduction.value)
          mu_cacheUsage.MultisetSort();
        SetBestResult(i, workingstate);
      }
  StateCopy(workingstate, &BestPermutedState);

  StateCopy(&temp, workingstate);
  ResetBestResult();
  for (i=0; i<Perm.count; i++)
    if (Perm.In(i))
      {
        StateCopy(workingstate, &temp);
        mu_memory.Permute(Perm,i);
        if (args->multiset_reduction.value)
          mu_memory.MultisetSort();
        SetBestResult(i, workingstate);
      }
  StateCopy(workingstate, &BestPermutedState);

  StateCopy(&temp, workingstate);
  ResetBestResult();
  for (i=0; i<Perm.count; i++)
    if (Perm.In(i))
      {
        StateCopy(workingstate, &temp);
        mu_proc.Permute(Perm,i);
        if (args->multiset_reduction.value)
          mu_proc.MultisetSort();
        SetBestResult(i, workingstate);
      }
  StateCopy(workingstate, &BestPermutedState);

};

/********************
 Canonicalization by fast simple variable canonicalization,
 fast simple scalarset array canonicalization,
 fast restriction on permutation set with simple scalarset array of scalarset,
 and fast exhaustive generation of
 all permutations for other variables
 ********************/
void SymmetryClass::Heuristic_Fast_Canonicalize(state* s)
{
  int i;
  static state temp;

  Perm.ResetToSimple();

  mu_memory.SimpleCanonicalize(Perm);

  if (Perm.MoreThanOneRemain()) {
    mu_proc.ArrayLimit(Perm);
  }

  if (Perm.MoreThanOneRemain()) {
    mu_proc.Limit(Perm);
  }

  Perm.SimpleToExplicit();

  StateCopy(&temp, workingstate);
  ResetBestResult();
  for (i=0; i<Perm.count; i++)
    if (Perm.In(i))
      {
        StateCopy(workingstate, &temp);
        mu_proc.Permute(Perm,i);
        if (args->multiset_reduction.value)
          mu_proc.MultisetSort();
        SetBestResult(i, workingstate);
      }
  StateCopy(workingstate, &BestPermutedState);

};

/********************
 Canonicalization by fast simple variable canonicalization,
 fast simple scalarset array canonicalization,
 fast restriction on permutation set with simple scalarset array of scalarset,
 and fast exhaustive generation of
 all permutations for other variables
 and use less local memory
 ********************/
void SymmetryClass::Heuristic_Small_Mem_Canonicalize(state* s)
{
  unsigned long cycle;
  static state temp;

  Perm.ResetToSimple();

  mu_memory.SimpleCanonicalize(Perm);

  if (Perm.MoreThanOneRemain()) {
    mu_proc.ArrayLimit(Perm);
  }

  if (Perm.MoreThanOneRemain()) {
    mu_proc.Limit(Perm);
  }

  Perm.SimpleToOne();

  StateCopy(&temp, workingstate);
  ResetBestResult();
  mu_proc.Permute(Perm,0);
  if (args->multiset_reduction.value)
    mu_proc.MultisetSort();
  BestPermutedState = *workingstate;
  BestInitialized = TRUE;

  cycle=1;
  while (Perm.NextPermutation())
    {
      if (args->perm_limit.value != 0
          && cycle++ >= args->perm_limit.value) break;
      StateCopy(workingstate, &temp);
      mu_proc.Permute(Perm,0);
      if (args->multiset_reduction.value)
        mu_proc.MultisetSort();
      switch (StateCmp(workingstate, &BestPermutedState)) {
      case -1:
        BestPermutedState = *workingstate;
        break;
      case 1:
        break;
      case 0:
        break;
      default:
        Error.Error("funny return value from StateCmp");
      }
    }
  StateCopy(workingstate, &BestPermutedState);

};

/********************
 Normalization by fast simple variable canonicalization,
 fast simple scalarset array canonicalization,
 fast restriction on permutation set with simple scalarset array of scalarset,
 and for all other variables, pick any remaining permutation
 ********************/
void SymmetryClass::Heuristic_Fast_Normalize(state* s)
{
  int i;
  static state temp;

  Perm.ResetToSimple();

  mu_memory.SimpleCanonicalize(Perm);

  if (Perm.MoreThanOneRemain()) {
    mu_proc.ArrayLimit(Perm);
  }

  if (Perm.MoreThanOneRemain()) {
    mu_proc.Limit(Perm);
  }

  Perm.SimpleToOne();

  mu_proc.Permute(Perm,0);
  if (args->multiset_reduction.value)
    mu_proc.MultisetSort();

};

/********************
  Include
 ********************/
#include "mu_epilog.hpp"
