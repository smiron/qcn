<? 
# Generate a random token for a transaction
include'token.php';   
$token = genToken();
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>QCN Purchase Form</title>
<script src="http://www.google.com/jsapi" type="text/javascript"></script>
<script type="text/javascript">
  google.load("jquery", "1.3.2");
</script>
<script src="_javascripts/address.js" type="text/javascript"></script>
<script src="_javascripts/validate.js" type="text/javascript"></script>
<link type="text/css" rel="stylesheet" href="_stylesheets/forms.css" media="screen" />
</head>
<body>

<div id="container">

  <h3>Quake Catcher Network $49 Sensor Order Form</h3>
  <form action="confirm.php" method="post" id="qcnpurchase">
    <fieldset>
      <h4>Billing Information:</h4><br />
      <label>Full Name</label>
      <input type="text" name="NAME" id="billname" />
    
      <label>Phone</label>
      <input type="text" name="PHONE" />
    
      <label>Email</label>
      <input type="text" name="EMAIL" />
    
      <label>Address</label>
      <input type="text" name="ADDRESS" id="billaddress" />
    
      <label>City</label>
      <input type="text" name="CITY" id="billcity" />
    
      <label>State/Province</label>  
      <select name="STATE" id="billstate">
        <option value="--">Select your state</option> <option value="--">Canada scroll down</option> <option value="AL">AL</option> <option value="AK">AK</option> <option value="AZ">AZ</option>
        <option value="AR">AR</option> <option value="CA">CA</option> <option value="CO">CO</option> <option value="CT">CT</option>
        <option value="DE">DE</option> <option value="DC">DC</option> <option value="FL">FL</option> <option value="GA">GA</option>
        <option value="HI">HI</option> <option value="ID">ID</option> <option value="IL">IL</option> <option value="IN">IN</option>
        <option value="IA">IA</option> <option value="KS">KS</option> <option value="KY">KY</option> <option value="LA">LA</option>
        <option value="ME">ME</option> <option value="MD">MD</option> <option value="MA">MA</option> <option value="MI">MI</option>
        <option value="MN">MN</option> <option value="MS">MS</option> <option value="MO">MO</option> <option value="MT">MT</option>
        <option value="NE">NE</option> <option value="NV">NV</option> <option value="NH">NH</option> <option value="NJ">NJ</option>
        <option value="NM">NM</option> <option value="NY">NY</option> <option value="NC">NC</option> <option value="ND">ND</option>
        <option value="OH">OH</option> <option value="OK">OK</option> <option value="OR">OR</option> <option value="PA">PA</option>
        <option value="RI">RI</option> <option value="SC">SC</option> <option value="SD">SD</option> <option value="TN">TN</option>
        <option value="TX">TX</option> <option value="UT">UT</option> <option value="VT">VT</option> <option value="VA">VA</option>
        <option value="WA">WA</option> <option value="WV">WV</option> <option value="WI">WI</option> <option value="WY">WY</option>
        <option value="AB">AB - Canada</option><option value="BC">BC - Canada</option><option value="MB">MB - Canada</option>
        <option value="NB">NB - Canada</option><option value="NL">NL - Canada</option><option value="NT">NT - Canada</option>
        <option value="NS">NS - Canada</option><option value="NU">NU - Canada</option><option value="ON">ON - Canada</option>
        <option value="NS">NS - Canada</option><option value="PE">PE - Canada</option><option value="QC">QC - Canada</option>
        <option value="NS">NS - Canada</option><option value="SK">SK - Canada</option><option value="YT">YT - Canada</option>

      </select>
      
      <div class="clearfix"></div>    
        <label>Zip / Postal Code</label>
      <input type="text" name="ZIP" id="billzip" class="num" />

      <div class="clearfix"></div>    
      <label>Country</label>
      <select name="COUNTRY" id="billcountry">
          <option selected="selected" value="USA">United States</option> <option value="CAN">Canada</option> 
      </select>
    </fieldset>

    <!-- Shipping information form -->
    <fieldset>
      
      <h4 style="float:left">Shipping Information:</h4>
      <div id="copy-checkbox">
        <input style="float:left" type="checkbox" class="box" id="sameAddress" name="sameAddress" onclick="myAddress();">
        <label class="for-checkbox" for="sameAddress">Same as Billing Address</label>
      </div>      
      <div class="spacer"></div>
      
      
      <label>Full Name</label>
      <input type="text" name="NAMETOSHIP" id="shipname" />
    
      <label>Address</label>
      <input type="text" name="ADDRESSTOSHIP" id="shipaddress" />
    
      <label>City</label>
      <input type="text" name="CITYTOSHIP" id="shipcity" />
    
      <label>State/Province</label>  
      <select name="STATETOSHIP" id="shipstate">
        <option value="--">Select your state</option> <option value="--">Canada scroll down</option>
        <option value="AL">AL</option> <option value="AK">AK</option> <option value="AZ">AZ</option>
        <option value="AR">AR</option> <option value="CA">CA</option> <option value="CO">CO</option> <option value="CT">CT</option>
        <option value="DE">DE</option> <option value="DC">DC</option> <option value="FL">FL</option> <option value="GA">GA</option>
        <option value="HI">HI</option> <option value="ID">ID</option> <option value="IL">IL</option> <option value="IN">IN</option>
        <option value="IA">IA</option> <option value="KS">KS</option> <option value="KY">KY</option> <option value="LA">LA</option>
        <option value="ME">ME</option> <option value="MD">MD</option> <option value="MA">MA</option> <option value="MI">MI</option>
        <option value="MN">MN</option> <option value="MS">MS</option> <option value="MO">MO</option> <option value="MT">MT</option>
        <option value="NE">NE</option> <option value="NV">NV</option> <option value="NH">NH</option> <option value="NJ">NJ</option>
        <option value="NM">NM</option> <option value="NY">NY</option> <option value="NC">NC</option> <option value="ND">ND</option>
        <option value="OH">OH</option> <option value="OK">OK</option> <option value="OR">OR</option> <option value="PA">PA</option>
        <option value="RI">RI</option> <option value="SC">SC</option> <option value="SD">SD</option> <option value="TN">TN</option>
        <option value="TX">TX</option> <option value="UT">UT</option> <option value="VT">VT</option> <option value="VA">VA</option>
        <option value="WA">WA</option> <option value="WV">WV</option> <option value="WI">WI</option> <option value="WY">WY</option>
        <option value="AB">AB - Canada</option><option value="BC">BC - Canada</option><option value="MB">MB - Canada</option>
        <option value="NB">NB - Canada</option><option value="NL">NL - Canada</option><option value="NT">NT - Canada</option>
        <option value="NS">NS - Canada</option><option value="NU">NU - Canada</option><option value="ON">ON - Canada</option>
        <option value="NS">NS - Canada</option><option value="PE">PE - Canada</option><option value="QC">QC - Canada</option>
        <option value="NS">NS - Canada</option><option value="SK">SK - Canada</option><option value="YT">YT - Canada</option>

      </select>
      <i>Canada at bottom</i>
      <div class="clearfix"></div>    
        <label>Zip / Postal Code</label>
      <input type="text" name="ZIPTOSHIP" id="shipzip" class="num" />
    
      <div class="clearfix"></div>
      <label>Country</label>
      <select name="COUNTRYTOSHIP" id="shipcountry">
          <option selected="selected" value="USA">United States</option> <option value="CAN">Canada</option> 
      </select>
      <cite><em>*QCN currently only ships inside the US and Canada.</em></cite>
    </fieldset>

    <fieldset>       
      <label>Quantity</label>
      <input type="text" name="QUANTITY" id="SENSOR49" class="num" value="0" />
      <p style="font-size:70%;"> &nbsp; @ $49.00 / sensor</p>
      <p id="total">Total purchase price: $0</p>
    </fieldset>

    <fieldset>
      <h4 style="float:left">Terms & Conditions:</h4>
      <p><textarea cols="57" rows="10" name="TANDC" align="justify">By clicking submit you agree to these terms:



      <p><input type="checkbox" name="accept_terms" checked="checked" disabled="disabled">I agree to QCN's Terms and Conditions.</p>
    </fieldset>

    <!-- Shipping information form -->
    <fieldset>
        <input type="hidden" name="TOKEN" value="<?= $token ?>">
        <input type="hidden" name="LOGIN" value="SUquake01Test">     

      <div class="spacer"></div>
      <input type="button" id="submitForm" class="button" value="Submit Order" style="width: 120px;">    
    </fieldset>

</div>    
    
</form>
</body>
</html>