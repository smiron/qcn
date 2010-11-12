#include "dlgsettings.h"
#ifdef _WIN32
#include "csensor_win_usb_jw.h"
#include "csensor_win_usb_jw24f14.h"
#else
#ifdef __APPLE_CC__
#include "csensor_mac_usb_jw.h"
#include "csensor_mac_usb_jw24f14.h"
#else
#include "csensor_linux_usb_jw.h"
#endif
#endif

/*
CDialogSettings::wxTextValidatorLatLng::wxTextValidatorLatLng(wxString* ptrStr, int iControl)
: wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, ptrStr)
{
    m_ptrString = ptrStr;
    m_iControl = iControl;
    as.Add("0");
    as.Add("1");
    as.Add("2");
    as.Add("3");
    as.Add("4");
    as.Add("5");
    as.Add("6");
    as.Add("7");
    as.Add("8");
    as.Add("9");
    as.Add("-");
    as.Add(".");
    SetIncludes(as);
}

bool CDialogSettings::wxTextValidatorLatLng::TransferToWindow()
{
}

bool wxTextValidatorLatLng::TransferFromWindow()
{
}

bool CDialogSettings::wxTextValidatorLatLng::Validate(wxWindow* parent)
{
    double dTest = atof(((wxTextCtrl*) parent)->GetValue().toAscii());
	if (m_bIsLat && (dTest < -90.0f || dTest > 90.0f)) return false;
    else if (!m_bIsLat && (dTest < -180.0f || dTest > 180.0f)) return false;
    return true;
}
*/


CDialogSettings::CDialogSettings(QWidget* parent, Qt::WindowFlags f)  : QDialog(parent, f)
{
	setModal(true);  // make it an application level modal window
	setWindowModality(Qt::ApplicationModal);
	setWindowTitle(tr("Edit QCNLive Preferences"));
	
    InitPointers();

    if (sm->dMyLatitude == NO_LAT) 
		m_strLatitude.clear();
    else
		m_strLatitude.sprintf("%.6g", sm->dMyLatitude);
	
    if (sm->dMyLongitude == NO_LNG) 
		m_strLongitude.clear();
    else
		m_strLongitude.sprintf("%.6g", sm->dMyLongitude);
	
    m_strStation = (char *) sm->strMyStation;
	
    m_strElevationMeter.sprintf("%.6g", sm->dMyElevationMeter);
    m_strElevationFloor.sprintf("%d", sm->iMyElevationFloor);
	
    CreateControls();
}


CDialogSettings::~CDialogSettings()
{
    if (m_psms) {
		delete m_psms;  
	    m_psms = NULL;
	}

    if (m_textctrlLatitude) delete m_textctrlLatitude;
    if (m_textctrlLongitude) delete m_textctrlLongitude;
	if (m_textctrlStation) delete m_textctrlStation;
	if (m_textctrlElevationFloor) delete m_textctrlElevationFloor;
	if (m_textctrlElevationMeter) delete m_textctrlElevationMeter;

	if (m_comboSensor) delete m_comboSensor;
	if (m_radioSAC) delete m_radioSAC;
	if (m_radioCSV) delete m_radioCSV;
	
	if (m_buttonSave) delete m_buttonSave;
	if (m_buttonCancel) delete m_buttonCancel;

}

void CDialogSettings::InitPointers()
{
    // init ptrs to null to test for deletion later
    m_textctrlLatitude = NULL; 
    m_textctrlLongitude = NULL; 
    m_textctrlStation = NULL; 
    m_textctrlElevationMeter = NULL; 
    m_textctrlElevationFloor = NULL; 
	
	m_psms = NULL;
	m_comboSensor = NULL;
	
	m_radioSAC = NULL;
	m_radioCSV = NULL;

    m_strLatitude.clear();
    m_strLongitude.clear();
    m_strStation.clear();
    m_strElevationMeter.clear();
    m_strElevationFloor.clear();
	
	m_buttonSave = m_buttonCancel = NULL;

    /*
    itemBoxSizer10 = NULL;

    // misc controls	
	itemBoxSizer2 = NULL;
	itemFlexGridSizer3 = NULL;
    itemFlexGridSizer5 = NULL;
	itemBoxSizer4 = NULL;
	itemStaticText6 = NULL;
	itemStaticText7 = NULL;
	itemStaticText8 = NULL;
	itemButton11 = NULL;
	itemButton12 = NULL;
    */

#ifdef _WIN32
	m_psms = new CSensorWinUSBJW;
#else
#ifdef __APPLE_CC__
	m_psms = new CSensorMacUSBJW;
#else
	m_psms = new CSensorLinuxUSBJW;
#endif
#endif
}

void CDialogSettings::SaveValues()
{
    double dTest = atof((const char*) m_strLatitude.toAscii());
    if (dTest >= -90.0f && dTest <= 90.0f)
        sm->dMyLatitude = dTest;

    dTest = atof((const char*) m_strLongitude.toAscii());
    if (dTest >= -180.0f && dTest <= 180.0f)
        sm->dMyLongitude = dTest;

    memset((char*) sm->strMyStation, 0x00, SIZEOF_STATION_STRING);
    strlcpy((char*) sm->strMyStation, (const char*) m_strStation.toAscii(), SIZEOF_STATION_STRING);	

    sm->dMyElevationMeter = atof((const char*) m_strElevationMeter.toAscii());
    sm->iMyElevationFloor = atoi((const char*) m_strElevationFloor.toAscii());
	
	// for the sensor combo, save the value of the combo -1 + SENSOR_USB_
	sm->iMySensor = -1;
	QString strCombo = m_comboSensor->currentText();
	for (int i = MIN_SENSOR_USB; i <= MAX_SENSOR_USB; i++)   {// usb sensors are between the values MIN & MAX_SENSOR_USB given in define.h
		if (!strCombo.compare(m_psms->getTypeStr(i))) { // strings match
			sm->iMySensor = i;
			break;
		}
	}

	if (m_radioCSV->isChecked()) sm->bMyOutputSAC = false;
	else if (m_radioSAC->isChecked()) sm->bMyOutputSAC = true;
	
}

void CDialogSettings::CreateControls()
{
	
	///////////////
	
    QGroupBox *packagesGroup = new QGroupBox(tr("qcn settings"));
	QGroupBox *buttonGroup = new QGroupBox();
	
    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;
	
    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());
	
    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));
	
    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);
	
	m_buttonSave = new QPushButton(tr("Save"));
	m_buttonCancel = new QPushButton(tr("Cancel"));
	
    QGridLayout *packagesLayout = new QGridLayout(this);
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

	QHBoxLayout* m_layoutButton = new QHBoxLayout(this);
    m_layoutButton->addWidget(m_buttonSave, 1, Qt::AlignLeft);
    m_layoutButton->addWidget(m_buttonCancel, 1, Qt::AlignRight);
	buttonGroup->setLayout(m_layoutButton);
	
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(buttonGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
	
	///////////	

	/*
    // misc controls	
	wxBoxSizer* itemBoxSizer2;
	wxFlexGridSizer* itemFlexGridSizer3;
	wxFlexGridSizer* itemFlexGridSizer5;
	wxBoxSizer* itemBoxSizer4;
	wxStaticText* itemStaticText6;
	wxStaticText* itemStaticText7;
	wxStaticText* itemStaticText8;
	wxStaticText* itemStaticText9;
	wxStaticText* itemStaticText10;
	wxStaticText* itemStaticText11;
	//wxStaticText* itemStaticText12;
	wxBoxSizer* itemBoxSizer10;
	wxButton* itemButton11;
	wxButton* itemButton12;

    itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemBoxSizer2);

    itemFlexGridSizer3 = new wxFlexGridSizer(1, 2, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer5 = new wxFlexGridSizer(5, 2, 0, 0);  // first param is number of rows, 2nd is number of columns
    itemBoxSizer4->Add(itemFlexGridSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // control 1 - Latitude
    itemStaticText6 = new wxStaticText;
    itemStaticText6->Create( this, wxID_STATIC, _("Latitude (-90 [SP] to 90 [NP]):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    m_textctrlLatitude = new wxTextCtrl;
    m_textctrlLatitude->Create( this, ID_TEXTCTRLLATITUDE, m_strLatitude, wxDefaultPosition, wxSize(100, -1),
         0, wxTextValidatorLatLng(&m_strLatitude, ID_TEXTCTRLLATITUDE)); 
    itemFlexGridSizer5->Add(m_textctrlLatitude, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // control 2 - Longitude
    itemStaticText7 = new wxStaticText;
    itemStaticText7->Create( this, wxID_STATIC, _("Longitude (-180 [W] to 180 [E]):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_textctrlLongitude = new wxTextCtrl;
    m_textctrlLongitude->Create( this, ID_TEXTCTRLLONGITUDE, m_strLongitude, wxDefaultPosition, wxSize(100, -1),
         0, wxTextValidatorLatLng(&m_strLongitude, ID_TEXTCTRLLONGITUDE)); 
    itemFlexGridSizer5->Add(m_textctrlLongitude, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // control 3 - Station Name
    itemStaticText8 = new wxStaticText;
    itemStaticText8->Create( this, wxID_STATIC, _("Station Name (7 chars max):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_textctrlStation = new wxTextCtrl;
    m_textctrlStation->Create( this, ID_TEXTCTRLSTATION, m_strStation, wxDefaultPosition, wxSize(100, -1),
         0, wxTextValidator(wxFILTER_ALPHANUMERIC, &m_strStation)); 
    itemFlexGridSizer5->Add(m_textctrlStation, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // control 4 - Elevation (meters)
    itemStaticText9 = new wxStaticText;
    itemStaticText9->Create( this, wxID_STATIC, _("Elevation (In Meters):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_textctrlElevationMeter = new wxTextCtrl;
    m_textctrlElevationMeter->Create( this, ID_TEXTCTRLELEVATIONMETER, m_strElevationMeter, wxDefaultPosition, wxSize(100, -1),
         0, wxTextValidatorLatLng(&m_strElevationMeter, ID_TEXTCTRLELEVATIONMETER));
    itemFlexGridSizer5->Add(m_textctrlElevationMeter, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);


    // control 5 - Elevation (floor #)
    itemStaticText10 = new wxStaticText;
    itemStaticText10->Create( this, wxID_STATIC, _("Floor # (-1 = Basement, 0 = Ground, etc):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_textctrlElevationFloor = new wxTextCtrl;
    m_textctrlElevationFloor->Create( this, ID_TEXTCTRLELEVATIONFLOOR, m_strElevationFloor, wxDefaultPosition, wxSize(100, -1),
         0, wxTextValidatorLatLng(&m_strElevationFloor, ID_TEXTCTRLELEVATIONFLOOR));
    itemFlexGridSizer5->Add(m_textctrlElevationFloor, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// control 6 & 7 -- radio buttons to pick CSV/text or SAC output
	m_radioCSV = new wxRadioButton;
	m_radioSAC = new wxRadioButton;
	m_radioCSV->Create(this, ID_RADIOCSV, _("Record CSV Text Files"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	m_radioSAC->Create(this, ID_RADIOSAC, _("Record SAC Files"), wxDefaultPosition, wxDefaultSize);
    itemFlexGridSizer5->Add(m_radioCSV, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    itemFlexGridSizer5->Add(m_radioSAC, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);	
	
	m_radioCSV->SetValue(!sm->bMyOutputSAC);
	m_radioSAC->SetValue(sm->bMyOutputSAC);
	
	
	// control 8 - combo box to force sensor selection (i.e. for demos/displays)
    itemStaticText11 = new wxStaticText;
    itemStaticText11->Create( this, wxID_STATIC, _("Force A Specific USB Sensor To Be Used:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	m_comboSensor = new wxComboBox;

	// create an array of strings of the USB sensor choices
	wxArrayString astrUSB;
	astrUSB.Add(_("No Preference"));
	for (int i = MIN_SENSOR_USB; m_psms && i <= MAX_SENSOR_USB; i++)   // usb sensors are between the values MIN & MAX_SENSOR_USB given in define.h
		astrUSB.Add(m_psms->getTypeStr(i));
	
	//bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "comboBox")
    m_comboSensor->Create(this, ID_COMBOSENSOR, m_strSensor, wxDefaultPosition, wxSize(200, -1), astrUSB, wxCB_READONLY, wxDefaultValidator, _("strCombo"));
	// set default setting if any
	if (sm->iMySensor < 0 || sm->iMySensor > MAX_SENSOR_USB || sm->iMySensor < MIN_SENSOR_USB)  
		m_comboSensor->SetValue(_("No Preference"));
	else
		if (m_psms) m_comboSensor->SetValue(m_psms->getTypeStr(sm->iMySensor));
			
    itemFlexGridSizer5->Add(m_comboSensor, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);	

    // OK & Cancel Buttons
    itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer3->Add(itemBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP|wxALL, 5);

    itemButton11 = new wxButton;
    itemButton11->Create( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton11->SetDefault();
    itemBoxSizer10->Add(itemButton11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemButton12 = new wxButton;
    itemButton12->Create( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(itemButton12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	 */

}
 

/*  CMC
void CDialogSettings::OnLatitudeUpdated( wxCommandEvent& WXUNUSED(event) )
{
    float fTest = atof(m_textctrlLatitude->GetValue().toAscii());
	if (fTest < -90.0f || fTest > 90.0f) {
         wxMessageBox(
            _T("Error: Latitude must be between -90 (South Pole) and 90 (North Pole)"), 
            _T("Latitude Validation Error")
         );
	 }
}

void CDialogSettings::OnLongitudeUpdated( wxCommandEvent& WXUNUSED(event) )
{
    float fTest = atof(m_textctrlLongitude->GetValue().toAscii());
	if (fTest < -180.0f || fTest > 180.0f) {
         wxMessageBox(
            _T("Error: Longitude must be between -180 (W) and 180 (E)\n(0 = Greenwich)"), 
            _T("Longitude Validation Error")
         );
	 }
}

void CDialogSettings::OnStationUpdated( wxCommandEvent& WXUNUSED(event) )
{
	int iLen = (int) m_textctrlStation->GetValue().Len();
    if ( iLen > SIZEOF_STATION_STRING-1 ) {
	     char *strErr = new char[_MAX_PATH];
		 sprintf(strErr, "Error: Station should be a maximum of %d alphanumeric characters in length, not %d", 
             SIZEOF_STATION_STRING-1, iLen);
         wxMessageBox(
            strErr, 
            _T("Station Validation Error")
         );
		 delete [] strErr;
		 return;
	}
}
*/
