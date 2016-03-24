function getDiskUsage() {
	$.get('/arduino/storage/', function(json_response){
		renderUsageBar(json_response.usage);
      }
    );  
}

function renderUsageBar(usage) {
    var data = usage.split(" ");
    data[0] = data[0].slice(0,-1) + ' ' + data[0].slice(-1);
    data[1] = data[1].slice(0,-1) + ' ' + data[1].slice(-1);
    deg = 360*data[2]/100;
    if (data[2] > 50) {
        $ppc.addClass('gt-50');
    }
    $('.ppc-progress-fill').css('transform','rotate('+ deg +'deg)');
    $('.ppc-percents span').html(data[2]+'%');
    $('.ppc-percents').addClass("loaded");
    $('.usage-label').text('Used: ' + data[0] + 'B of ' + data[1] + 'B');
}

function restartDevice() {
  $('.button.download').toggleClass('disabled').text('restarting...');
  setTimeout(function() {
    $('.button.download').text('Device Ready');
  }, 120000);
  $.get('/arduino/reboot/');
}

window.onload = getDiskUsage;
