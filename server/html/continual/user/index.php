<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

// This is a template for your web site's front page.
// You are encouraged to customize this file,
// and to create a graphical identity for your web site
// my developing your own stylesheet
// and customizing the header/footer functions in html/project/project.inc

require_once("../inc/db.inc");
require_once("../inc/util.inc");
require_once("../inc/news.inc");
require_once("../inc/cache.inc");
require_once("../inc/uotd.inc");
require_once("../inc/sanitize_html.inc");
require_once("../inc/text_transform.inc");
require_once("../project/project.inc");

check_get_args(array());

function qcn_show_map()  {

// begin map stuff

echo "<BR><p><h2>".tra("Trigger Map")."</h2>";

echo "
    Latest Triggers Recorded (Past 4 Hours) - Generated on " . date("F d Y H:i:s", filectime(MAP_TRIGGER)) . " UTC";

echo "
    <p><A HREF=maptrig.php>Click here or on a region of the map for an interactive Google map</A>
    <p>Legend: Blue triangle = QCN participant trigger, Red circle = Earthquake of minimum magnitude " . MIN_MAGNITUDE . "
    <p><i>Note: locations changed at the kilometer-level to protect privacy, unless participant authorized exact location be used</i>
     ";

echo "
<IMG SRC=\"" . MAP_TRIGGER . "\" usemap=\"#" . MAP_TRIGGER . "\" border=\"0\">
<map name=\"" . MAP_TRIGGER . "\">
        <area shape=\"rect\" coords=\"0,2,225,232\" href=\"maptrig.php?cx=38&cy=-120\">
        <area shape=\"rect\" coords=\"2,236,228,511\" href=\"maptrig.php?cx=-20&cy=-120\">
        <area shape=\"rect\" coords=\"227,3,428,234\" href=\"maptrig.php?cx=38&cy=-70\">
        <area shape=\"rect\" coords=\"231,238,442,510\" href=\"maptrig.php?cx=-20&cy=-70\">
        <area shape=\"rect\" coords=\"430,3,605,237\" href=\"maptrig.php?cx=50&cy=1\">
        <area shape=\"rect\" coords=\"445,241,732,510\" href=\"maptrig.php?cx=-10&cy=5\">
        <area shape=\"rect\" coords=\"609,3,803,239\" href=\"maptrig.php?cx=38&cy=80\">
        <area shape=\"rect\" coords=\"735,244,1022,511\" href=\"maptrig.php?cx=-20&cy=140\">
        <area shape=\"rect\" coords=\"806,3,1021,243\" href=\"maptrig.php?cx=38&cy=140\">
</map>
    ";

echo "
    <p><A HREF=maptrigtime.php>Click here for trigger maps for the past day / week / month</A>";

// end map stuff
echo "<BR><p><h2>".tra("Participants by Week")."</h2>";

echo "
    <img src=\"img/weekly.png\" alt=\"Weekly QCN Participant Machines\">
    ";

}


function show_nav() {
    $config = get_config();
    $master_url = parse_config($config, "<master_url>");
    $no_computing = parse_config($config, "<no_computing>");
    $no_web_account_creation = parse_bool($config, "no_web_account_creation");
    $user = get_logged_in_user(false);
    echo "<div class=\"mainnav\">
        <h2 class=headline>About ".PROJECT."</h2>
    ";
     echo "
        The Quake Catcher Network (QCN) is a research project that uses Internet-connected
        computers to do research, education, and outreach in seismology.
        You can participate by downloading and running a free program
        on your computer.  Currently only certain Mac (OS X) PPC and Intel laptops are supported --
        recent ones which have a built-in accelerometer.  You can also buy an external USB accelerometer.
        <p>
        QCN is based at the Stanford University School of Earth Sciences.
        <ul>
        <li> <A HREF=\"" . BASEURL . "/index.php\">Quake Catcher Network Home Page</A>
        <li> <A HREF=\"" . BASEURL . "/about-qcn/contact-us\">Project Personnel</A>
        </ul>
       ";

    if ($no_computing) {
        echo "
            <li> <a href=\"create_account_form.php\">Create an account</a>
        ";
    } else {
        echo "
            <li><a href=\"info.php\">".tra("Read our rules and policies")."</a>
            <li> This project uses BOINC.
                If you're already running BOINC, select Add Project.
                If not, <a target=\"_new\" href=\"http://boinc.berkeley.edu/download.php\">download BOINC</a>.
            <li> When prompted, enter <br><b>".$master_url."</b>
        ";
        if (!$no_web_account_creation) {
            echo "
                <li> If you're running a command-line version of BOINC,
                    <a href=\"create_account_form.php\">create an account</a> first.
            ";
        }
        echo "
            <li> If you have any problems,
                <a target=\"_new\" href=\"http://boinc.berkeley.edu/wiki/BOINC_Help\">get help here</a>.
        ";
    }
    echo "
        </ul><BR><p>

        <h2 class=headline>Returning participants</h2>
        <ul>
    ";
    if ($no_computing) {
        echo "
            <li><a href=\"bossa_apps.php\">Do work</a>
            <li><a href=\"home.php\">Your account</a> - view stats, modify preferences
            <li><a href=\"team.php\">Teams</a> - create or join a team
        ";
    } else {
        echo "
            <li><a href=\"home.php\">Your account</a> - view stats, modify preferences
            <li><a href=server_status.php>Server status</a>
            <li><a href=\"team.php\">Teams</a> - create or join a team
            <li><a href=\"cert1.php\">Certificate</a>
            <li><a href=\"apps.php\">".tra("Applications")."</a>
        ";
    }
    echo "
        </ul>
        <h2 class=headline>".tra("Community")."</h2>
        <ul>
        <li><a href=\"user_search.php\">User search</a>
        <li><a href=\"forum_index.php\">".tra("Message boards")."</a>
        <li><a href=\"stats.php\">Statistics</a>
        <li><a href=language_select.php>Languages</a>
        </ul>
    ";


// CMC changed to forum prefs 4th bit
  if (qcn_admin_user_auth($user)) {  // defined in project/project.inc
       echo "
        <h2>".tra("Extra Links")."</h2>
        <ul>
        <li><a href=\"trdl.php\">".tra("Trigger Search/Upload/Download Page")."</a>
        <li><a href=\"ramp.php\">".tra("View RAMP Signups")."</a>
        <li><a href=\"" . BASEURL . "/sensor/todo\">".tra("To-Do List")."</a></ul>";
        
        //if ($user->id == 15) {
        // check for db replication timestamp
        #$kewfile = BASEPATH . "/boinc/sensor/html/user/max.txt";
        #if (file_exists($kewfile) && ($handle = fopen($kewfile, 'r'))) {
        #      $output = fgets($handle); // skip first line
        #      $output = fgets($handle);              fclose($handle);
        #      echo "        <li>Kew Sync Diff (seconds): " . $output . "<BR>(should be a small number else server is down) <BR>";
     #   }        else {
     #         echo "        <li>No Replication Sync File on Kew - Better Check!";
     # }
   }

   qcn_show_map();
   echo "     </div>";

}

$stopped = web_stopped();
$rssname = PROJECT . " RSS 2.0" ;
$rsslink = URL_BASE . "rss_main.php";

page_head(PROJECT);
/*
header("Content-type: text/html; charset=utf-8");


echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">";


echo "<html>
    <head>
    <title>".PROJECT."</title>
    <link rel=\"stylesheet\" type=\"text/css\" href=\"main.css\" media=\"all\" />
    <link rel=\"stylesheet\" type=\"text/css\" href=\"".STYLESHEET."\">
    <link rel=\"alternate\" type=\"application/rss+xml\" title=\"".$rssname."\" href=\"".$rsslink."\">
";
include 'schedulers.txt';
echo "
    </head><body>
    <div class=page_title>".PROJECT."</div>
";
*/

include 'schedulers.txt';

echo "
    <table cellpadding=\"8\" cellspacing=\"4\" class=bordered>
    <tr><td rowspan=\"2\" valign=\"top\" width=\"40%\">
";

if ($stopped) {
    echo "
        <b>".PROJECT." is temporarily shut down for maintenance.
        Please try again later</b>.
    ";
} else {
    db_init();
    show_nav();
}

echo "
    <p>
    <a href=\"http://boinc.berkeley.edu/\"><img align=\"middle\" border=\"0\" src=\"img/pb_boinc.gif\" alt=\"Powered by BOINC\"></a>
    </p>
    </td>
";

/*
if (!$stopped) {
    $profile = get_current_uotd();
    if ($profile) {
        echo "
            <td class=uotd>
            <h2 class=headline>".tra("User of the day")."</h2>
        ";
        show_uotd($profile);
        echo "</td></tr>\n";
    }
}
*/

echo "
    <tr><td class=news>
    <h2 class=headline>News</h2>
    <p>
";
include("motd.php");
show_news(0, 10);
echo "
    </td>
    </tr></table>
";

page_tail_main();

?>
