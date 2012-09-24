if ARGV.size!=4
	puts "Usage:"
	puts "ruby coreceptorUsage.rb file mappingR5 mappingX4 mappingR5X4"
	exit
end

examples=ARGV[0]
mapping_R5=ARGV[1]
mapping_X4=ARGV[2]
mapping_R5X4=ARGV[3]

f=File.open examples
while line=f.gets
	tokens=line.split " "
	tropism=tokens.first.strip
	index=tokens.last
	output=mapping_R5
	if tropism=='X4'
		output=mapping_X4
	elsif tropism=='R5X4'
		output=mapping_R5X4
	end
	puts "#{output} # #{index}"
end
f.close
