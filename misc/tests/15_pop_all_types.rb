require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
r = system "./avm #{test} > #{output}"

if r
    fd = File.open(output, "rb")
    content = fd.read
    should_equal("4242\n32\n42424242\n32\n42424242\n32\n0.42424242\n32\n32\n", content, file)
else
    puts "Error returned by avm !".red
end