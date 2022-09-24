```javascript
<html>
  <body>
    <script>
    	alert("Hello,World");
	</script>
  </body>
</html>
```



123



```javascript
<html>
  <body>
    <script>
    	//alert("Hello,World");

      /*var usr;
      usr=prompt("What's your name? ");
      alert("Hello, "+usr);*/

      /*var num,sum;
      sum=0;
      num=prompt("Enter new value, or 0 to end");
      while(num!=0){
        sum=sum+num;
        num=prompt("Enter new value, or 0 to end");
      }
      alert("sum= "+sum);*/

      function initialize (){
        var latlong= new google.maps. Lating(38.89768,-77.0365);
        var opts={
          zoom:18,
          center: latlong,
          mapTypeld:google.maps .MapTypeId. HYBRID
        };
        var map=new google.maps. Map(
          document.getElementById ( "map" ) , opts) ;
          var marker=new google.maps.Marker({
            position: latlong,
            map: map
          });
        }
	</script>
  </body>
</html>
```

