  <!-- <?php
  //sudo /etc/init.d/apache2 stop
  //sudo /opt/lampp/lampp restart
  $parallel_test = $_GET['parallel_test'];
  if($parallel_test == "on")
  {
    $file = fopen("parallel_test.json", "w") or die("can't open file");
    fwrite($file, '{"parallel_test": "on"}');
    fclose($file);
  }

  else if ($parallel_test == "off")
  {
    $file = fopen("parallel_test.json", "w") or die("can't open file");
    fwrite($file, '{"parallel_test": "off"}');
    fclose($file);
  }
?> -->

<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>Driving Licence Test</title>

    <script src="https://code.jquery.com/jquery-2.1.4.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css">
    <script>
      function parallel_park_start()
      {
        var url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field3=1"
        $.getJSON(url, function(data)
        {
          console.log(data);
          document.getElementById("status_parallel").innerHTML = "Parallel Parking Test has begun :)";
        });
      }

      function parallel_park_end()
      {
        var url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field3=0"
        $.getJSON(url, function(data)
        {
          console.log(data);
          document.getElementById("status_parallel").innerHTML = "Parallel Parking Test has ended :)";
        });
      }

      function drive_uphill_start()
      {
        var url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field5=1"
        $.getJSON(url, function(data)
        {
          console.log(data);
          document.getElementById("status_uphill").innerHTML = "Drive Uphill test has begun :)";
        });
      }

      function test_8_start()
      {
        var url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field7=1"
        $.getJSON(url, function(data)
        {
          console.log(data);
          document.getElementById("status_8").innerHTML = "Test 8 Test has begun :)";
        });
      }

      function test_8_end()
      {
        var url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field7=0"
        $.getJSON(url, function(data)
        {
          console.log(data);
          document.getElementById("status_8").innerHTML = "Test 8 Test has ended :)";
        });
      }

      function submit()
      {
        var url = "https://thingspeak.com/channels/352887/field/3/last.html";
        $.getJSON(url, function(data)
        {
          if(data=="4")
            document.getElementById("parallel_park").innerHTML = "Parallel Parking Test Success :)";
          if(data=="3")
            document.getElementById("parallel_park").innerHTML = "Parallel Parking Test Failure :(";
        });

        url = "https://thingspeak.com/channels/352887/field/5/last.html";
        $.getJSON(url, function(data)
        {
          if(data=="4")
            document.getElementById("drive_uphill").innerHTML = "Driving Uphill Test Success :)";
          if(data=="3")
            document.getElementById("drive_uphill").innerHTML = "Driving Uphill Test Failure :(";
        });

        url = "https://thingspeak.com/channels/352887/field/7/last.html";
        $.getJSON(url, function(data)
        {
          if(data=="4")
            document.getElementById("test_8").innerHTML = "Test 8 Success :)";
          if(data=="3")
            document.getElementById("test_8").innerHTML = "Test 8 Failure :(";
        });

        url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field3=0"
        $.getJSON(url, function(data)
        {
          console.log(data);
        });

        url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field5=0"
        $.getJSON(url, function(data)
        {
          console.log(data);
        });

        url = "http://api.thingspeak.com/update?api_key=WTPWUIP2YE2PMPNC&field7=0"
        $.getJSON(url, function(data)
        {
          console.log(data);
        });

      }
    </script>
  </head>
  <body>
    <div class="row" style="margin-top: 20px;">
      <div class="col-md-8 col-md-offset-2">
        <button class="btn btn-success btn-block btn-lg" onclick="parallel_park_start()">Start Parallel Parking Test</button>
        <br />
        <button class="led btn btn-danger btn-block btn-lg" onclick="parallel_park_end()">Finish Parallel Parking Test</button>
        <br />
        <div id="status_parallel" class="light-status well" style="margin-top: 5px; text-align:center"></div>
        <br /><br />
        <button class="btn btn-success btn-block btn-lg" onclick="drive_uphill_start()">Start Drive Uphill Test</button>
        <br />
        <div id="status_uphill" class="light-status well" style="margin-top: 5px; text-align:center"></div>
        <br /><br />
        <button class="btn btn-success btn-block btn-lg" onclick="test_8_start()">Start 8 Test</button>
        <br />
        <button class="led btn btn-danger btn-block btn-lg" onclick="test_8_end()">Finish 8 Test</button>
        <br /><br /><br />
        <button class="led btn btn-danger btn-block btn-lg" onclick="submit()">Submit</button>
        <br />
        <div id="status_8" class="light-status well" style="margin-top: 5px; text-align:center"></div>
        <br /><br />
        <div id="parallel_park" class="light-status well" style="margin-top: 5px; text-align:center"></div>
        <div id="drive_uphill" class="light-status well" style="margin-top: 5px; text-align:center"></div>
        <div id="test_8" class="light-status well" style="margin-top: 5px; text-align:center"></div>
      </div>
    </div>
  </body>
</html>
