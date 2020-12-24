#ifndef H_BACKGLASS_CAMERA_PROPERTY
#define H_BACKGLASS_CAMERA_PROPERTY

class BackglassCameraProperty : public BasePropertyDialog
{
public:
    BackglassCameraProperty(const VectorProtected<ISelect>* pvsel);
    virtual ~BackglassCameraProperty()
    {
    }

    void UpdateVisuals(const int dispid=-1);
    void UpdateProperties(const int dispid);

protected:
    virtual BOOL OnInitDialog();

private:
    HWND            m_hFssModeCheck;
    HWND            m_hTestDesktopCheck;
    ComboBox        m_modeCombo;
    EditBox         m_inclinationEdit;
    EditBox         m_fovEdit;
    EditBox         m_laybackEdit;
    EditBox         m_xyRotationEdit;
    EditBox         m_xScaleEdit;
    EditBox         m_yScaleEdit;
    EditBox         m_zScaleEdit;
    EditBox         m_xOffsetEdit;
    EditBox         m_yOffsetEdit;
    EditBox         m_zOffsetEdit;
    vector<string>  m_modeList;
};

#endif // !H_BACKGLASS_CAMERA_PROPERTY
