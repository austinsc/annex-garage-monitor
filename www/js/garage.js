var interval;

// EDIT NUMBER OF GARAGES HERE
var GARAGES = 2;


function garageClick(obj) {
  // Grey out icon and disable click - see css for .disabled
	$(obj).addClass("disabled");

  // Send signal to motor, wait for response from Arduino
  $.ajax({
    url: "/arduino/motor/" + obj.id.slice(-1),
    dataType: 'json',
    error: function() {
      alert("Cannot reach garage monitor. Please try again.");
      $(obj).removeClass("disabled");
    },
    success: function() {
      // Set icon to yellow to indicate motor is running
      $(obj).removeClass("disabled").addClass("running");

      // After 10 seconds (motor finished running), re-enable icon
      setTimeout(function() {
        $(obj).removeClass("running");
      }, 10000);
    },
    timeout: 30000
  });

}

function lightsClick(obj) {
  // Grey out icon and disable click - see css for .disabled
  $(obj).addClass("disabled");

  // Send signal to motor, wait for response from Arduino
  $.ajax({
    url: "/arduino/lights/",
    dataType: 'json',
    error: function() {
      alert("Cannot reach garage monitor. Please try again.");
      $(obj).removeClass("disabled");
    },
    success: function() {
      $(obj).removeClass("disabled").addClass("running");

      // After 10 seconds (motor finished running), re-enable icon
      setTimeout(function() {
        $(obj).removeClass("running");
      }, 10000);
    },
    timeout: 30000
  });

}


function setGarageStatus(label, val) {
  var selector = '#' + label;
  if (val === 0) {
    $(selector + ' > .garage').removeClass("open").addClass("closed");
    $(selector + ' > h3').text("closed");
  } else {
    $(selector + ' > .garage').removeClass("closed").addClass("open");
    $(selector + ' > h3').text("open");
  }

}

function refresh() {

  $.get('/arduino/inputs/', function(json_response){
            for ( var i = 0; i < GARAGES; i++ ) {
              setGarageStatus("sensor" + i, json_response["sensor" + i]);
            }

            // IF JUST ONE GARAGE, REMOVE THE UPPER "FOR" LOOP AND UNCOMMENT BELOW
            // setGarageStatus("sensor0", json_response.sensor0);
          }
        );

}

function saveScreenshot() {
  $(".button.special").toggleClass("disabled");

  var timestamp = getFileNameTimestamp();
  $.get('/arduino/screenshot/' + timestamp, function(){
      $(".button.special").toggleClass("disabled");
  });
}

function getFileNameTimestamp(){
  var now = new Date();
  var date = [ now.getMonth() + 1, now.getDate(), now.getFullYear() ];
  var time = [ now.getHours(), now.getMinutes(), now.getSeconds() ];

  // If hour is 0, set it to 12
  time[0] = time[0] || 12;

  for ( var i = 0; i < 3; i++ ) {
    // If HH, mm, SS are less than 10, add a zero
    if ( time[i] < 10 ) {
      time[i] = "0" + time[i];
    }

    // If MM, dd, YYYY are less than 10, add a zero
    if ( date[i] < 10 ) {
      date[i] = "0" + date[i];
    }
  }

  return date.join("") + time.join("");
}

function getTimestamp(){
  var now = new Date();
  date = [ now.getMonth() + 1, now.getDate(), now.getFullYear() ];
  time = [ now.getHours(), now.getMinutes(), now.getSeconds() ];
  suffix = ( time[0] < 12 ) ? "AM" : "PM";
  time[0] = ( time[0] < 12 ) ? time[0] : time[0] - 12;
  time[0] = time[0] || 12;
  for ( var i = 1; i < 3; i++ ) {
    if ( time[i] < 10 ) {
      time[i] = "0" + time[i];
    }
  }

  return date.join("/") + " " + time.join(":") + " " + suffix;

}

function refreshScreenshot() {
  $(".fa-refresh").toggleClass("fa-spin");
  setTimeout(function() {
    $('#garage-cam').attr('src', "http://192.168.0.28:8080/?action=snapshot");
    $('#last-updated').text(getTimestamp());
    $(".fa-refresh").toggleClass("fa-spin");
  }, 2000);
}

interval = window.setInterval(refresh, 2000);
$(window).load(function()
  {
    $('#last-updated').text(getTimestamp());
  });