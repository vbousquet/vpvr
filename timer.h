// Timer.h: Definition of the Timer class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#if !defined(AFX_TIMER_H__932D477C_A594_4941_906D_8BF11A68C838__INCLUDED_)
#define AFX_TIMER_H__932D477C_A594_4941_906D_8BF11A68C838__INCLUDED_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Timer

class TimerDataRoot
{
public:
   int m_TimerInterval;
   bool m_TimerEnabled;
};

class TimerData final
{
public:
   TimerDataRoot m_tdr;
   Vertex2D m_v;
};

class Timer :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IDispatchImpl<ITimer, &IID_ITimer, &LIBID_VPinballLib>,
   //public ISupportErrorInfo,
   //public CComObjectRoot,
   public CComCoClass<Timer, &CLSID_Timer>,
   //public CComCoClass<Flipper, &CLSID_Flipper>,
   //public IDispatchImpl<IFlipper, &IID_IFlipper, &LIBID_VPinballLib>,
   public IConnectionPointContainerImpl<Timer>,
   public IProvideClassInfo2Impl<&CLSID_Timer, &DIID_ITimerEvents, &LIBID_VPinballLib>,
   public EventProxy<Timer, &DIID_ITimerEvents>,
   public ISelect,
   public IEditable,
   public IScriptable,
   public IFireEvents,
   public Hitable
   //public EditableImpl<Timer>
{
public:
   Timer();
   virtual ~Timer();

   //HRESULT Init(PinTable *ptable, float x, float y);

   BEGIN_COM_MAP(Timer)
      COM_INTERFACE_ENTRY(IDispatch)
      COM_INTERFACE_ENTRY(ITimer)
      //COM_INTERFACE_ENTRY(ISupportErrorInfo)
      COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
      COM_INTERFACE_ENTRY(IProvideClassInfo)
      COM_INTERFACE_ENTRY(IProvideClassInfo2)
   END_COM_MAP()

   BEGIN_CONNECTION_POINT_MAP(Timer)
      CONNECTION_POINT_ENTRY(DIID_ITimerEvents)
   END_CONNECTION_POINT_MAP()

   void MoveOffset(const float dx, const float dy) final;
   void SetObjectPos() final;
   // Multi-object manipulation
   Vertex2D GetCenter() const final;
   void PutCenter(const Vertex2D& pv) final;

   void RenderBlueprint(Sur *psur, const bool solid) final;
   ItemTypeEnum HitableGetItemType() const final { return eItemTimer; }

   void WriteRegDefaults() final;

   STANDARD_EDITABLE_DECLARES(Timer, eItemTimer, TIMER, 3)

   //DECLARE_NOT_AGGREGATABLE(Timer)
   // Remove the comment from the line above if you don't want your object to
   // support aggregation.

   DECLARE_REGISTRY_RESOURCEID(IDR_TIMER)
   // ISupportsErrorInfo
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

   // ITimer
   STDMETHOD(get_Interval)(/*[out, retval]*/ long *pVal);
   STDMETHOD(put_Interval)(/*[in]*/ long newVal);
   STDMETHOD(get_Enabled)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_Enabled)(/*[in]*/ VARIANT_BOOL newVal);

   TimerData m_d;

private:
   PinTable *m_ptable;
};

#endif // !defined(AFX_TIMER_H__932D477C_A594_4941_906D_8BF11A68C838__INCLUDED_)
